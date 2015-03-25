#ifndef GRAPHE_H
#define GRAPHE_H
#include <vector>
#include <fstream>
#include <string>
#include <ostream>
#include <istream>
#include <sstream>
#include "../Outils/exception.h"
#include "sommet.h"
#include "arete.h"
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <streambuf>
#include <math.h>
#include "etiquette.h"

using std::unordered_map;
using std::max;
using std::pair;
using std::fstream;
using std::ostringstream;
using std::endl;
using std::ostream;
using std::ofstream;
using std::istream;
using std::string;
using std::streambuf;
using std::stringstream;



/**
 * @brief The Graphe class
 * Cette classe représente un graphe.
 * Elle est définie par une liste de sommets ainsi qu'une liste d'arêtes.
 */
class Graphe{

private:
    vector<Sommet*> sommets;
    vector<Arete> aretes;
    unordered_map< Sommet* , vector<Sommet*> > successeurs;

public:
    string name;

    /**
     * @brief Graphe
     * @param s
     */
    Graphe(const string &s):
        name(s){}


    /**
     * @brief add_sommet
     * Ajoute un sommet au graphe.
     * @param s
     */
    inline void add_sommet(const Sommet &s){
        if( find_sommet(s.name) != NULL){
         throw Exception("sommet déjà existant");
        }
        sommets.push_back(new Sommet(s));
    }



    /**
     * @brief add_successor
     * @param from
     * @param to
     */
    inline void add_successor( Sommet *from, Sommet *to){
        if(successeurs.find(from) != successeurs.end()){
            successeurs[from].push_back(to);
        }
        else{
            successeurs.insert(pair< Sommet*, vector< Sommet* > >(from, vector< Sommet*>() ));
            successeurs[from].push_back(to);
        }
    }


    /**
     * @brief add_arete
     * Ajoute une arête au graphe
     * @param a
     */
    inline void add_arete(const Arete &a){
        aretes.push_back(a);
        add_successor(a.from,a.to);
    }


    /**
     * @brief add_arete
     * Ajoute une arête au graphe
     * @param from
     * @param to
     * @param cost
     * @param resource
     */
    inline void add_arete(const string &from, const string &to, const double cost, const double resource){
        add_arete(Arete(get_sommet(from),get_sommet(to),cost,resource));

    }


    /**
     * @brief ~Graphe
     */
    virtual ~Graphe(){
        for(Sommet* s: sommets){
            delete s;
        }
    }


    /**
     * @brief find_sommet
     * Recherche si le sommet identifié par son nom est contenu dans le graphe.
     * @param name
     * @return
     */
    inline Sommet* find_sommet(const string &name){
        for(Sommet* s: sommets){
            if(s->name == name){
                return s;
            }
        }
        return NULL;
    }

    /**
     * @brief find_sommet
     * @param s
     * @return le sommet dans le graphe ayant le même nom
     */
    inline Sommet* find_sommet(const Sommet &s){
        return find_sommet(s.name);
    }

    /**
     * @brief get_sommet
     * @param name
     * @return le sommet dans le graphe ayant le même nom, s'il n'existe pas lève une exception
     */
    inline Sommet* get_sommet(const string &name){
        Sommet* s(find_sommet(name));
        if(s == NULL){
            throw Exception("le sommet " + name + " n'existe pas dans le graphe");
        }
        return s;
    }

    /**
     * @brief correction_etiquette
     * @param from
     * @param to
     * @param choisir
     * @param pareto
     * @return
     */
    vector<Arete> correction_etiquette(const string &from, const string &to,Sommet* choisir(vector<Sommet*> &list), vector<Etiquette*> pareto(const vector<Etiquette*> &list), bool borne_min ){
        Sommet* f(get_sommet(from)) , *t(get_sommet(to));
        return correction_etiquette(*f,*t,choisir,pareto,borne_min);
    }





    /**
     * @brief shortest_path
     * @param to
     * @return
     */
    vector<Arete> shortest_path( const Sommet *to){
        //TODO: variantes
        vector<Arete> path;
        const Etiquette* best = to->tags[0];
        for(Etiquette* e : to->tags){
            if(e->cost < best->cost){
                best = e;
            }
        }
        const Sommet* current = best->to;
        while(best->from){
            best = best->from;
            path.push_back(get_arete(best->to,current));
            current = best->to;
        }

        return path;
    }

    /**
     * @brief correction_etiquette
     * @param from
     * @param to
     * @param choisir
     * @param pareto
     * @return
     */
    vector<Arete> correction_etiquette(const Sommet &from, const Sommet &to,Sommet* choisir(vector<Sommet*> &list), vector<Etiquette*> pareto(const vector<Etiquette*> &list), bool borne_min ){

        if(sommets.size() > 0){

            Sommet* source(find_sommet(from)), *puit(find_sommet(to));

            //On réinitialise les tags
            for(Sommet* s: sommets){
                for(Etiquette* e : s->tags){
                    delete e;
                }
                s->tags.clear();
            }
            vector<Sommet*> list;
            list.push_back(source);

            Sommet* xi;
            source->add_default_tag();
            while(list.size() > 0){

                xi = choisir(list);

                for(Sommet* xj : successeurs[xi]){

                    for(Etiquette* e: xi->tags){

                        Arete tmp = get_arete(xi,xj);
                        Etiquette e_prime(e, xj, e->cost + tmp.cost, e->resources + tmp.resource);
                        if(borne_min && e_prime.resources < xj->min_resource){
                            e_prime.resources = xj->min_resource;
                        }
                        if( e_prime.resources <= xj->max_resource ){

                            xj->add_tag(e_prime);
                            Etiquette* e_prime_pointer = xj->tags.back();
                            xj->tags = pareto(xj->tags);
                            //on test si e_prime_pointer est bien dans la liste retournée par pareto, comme l'orde est conservé, c'est le dernier de la liste
                            if(e_prime_pointer == xj->tags.back()){
                                if(std::find(list.begin(),list.end(),xj) == list.end()){
                                    list.push_back(xj);
                                }
                            }

                        }
                    }
                }
            }
            return shortest_path(puit);
        }
        else{
            throw Exception("Il n'y a pas assez d'arete dans le graphe");
        }
    }




    /**
     * @brief get_arete
     * Retourne une arête identifiée par son sommet source et destination
     * @param from
     * @param to
     * @return
     */
    inline Arete get_arete(const Sommet *from, const Sommet *to){
        for(Arete a : aretes){
            if(a.from == from and a.to == to){
                return a;
            }
        }
        throw Exception("l'arete " + from->name + " => " + to->name + " n'existe pas dans le graphe");
    }


    /**
     * @brief get_arete
     * Retourne une arête identifiée par le nom de son sommet source et destination
     * @param from
     * @param to
     * @return
     */
    inline Arete get_arete(const string &from, const string &to){
        return get_arete(find_sommet(from),find_sommet(to));
    }


    /**
     * @brief operator string
     */
    operator string () const{
        ostringstream oss;
        oss << "GRAPHE (" << endl;
        oss << "name = " << name << endl;

        oss << "SOMMETS (" << endl;
        for(Sommet* s : sommets){
            oss << (string) *s << endl;
        }
        oss << ")" << endl;

        oss << "ARETES (" << endl;
        for(Arete a : aretes){
            oss << (string) a << endl;
        }
        oss << "))" << endl;

        return oss.str();
    }

    /**
     * @brief formatDuProf
     * @param G
     * @return
     */
    static string formatDuProf(const Graphe& G){
        ostringstream oss;
        oss << "# Graphe N = " << G.sommets.size() << " ; M = " << G.aretes.size() << endl;
        oss << endl << "ressource 1" << endl;

        oss << endl << "sectionSommets" << endl;
        for(Sommet* s : G.sommets){
            oss << s->name << "\t" << s->min_resource << "\t" << s->max_resource << endl;
            for(Etiquette* e : s->tags){
                oss << s->name << "  " << e->cost << "  " << e->resources << endl;
            }
        }

        oss << endl << "sources" << endl;
        oss << "...TO DO..."<< endl;

        oss << endl << "puits" << endl;
        oss << "...TO DO..."<< endl;

        oss << endl << "sectionArcs" << endl;
        for(Arete a : G.aretes){
            oss << a.from->name << "\t" << a.to->name << "\t" << a.cost << "\t" << a.resource << endl;
        }

        oss << endl << "sectionGraphes" << endl;

        return oss.str();
    }

    /**
     * @brief getVArete
     * @return
     */
    const vector<Arete>& getVArete() const{
        return this->aretes;
    }

//    string toString()const {
//        ostringstream ser;
//        ser.flush();
//        for(Arete a : this->aretes){
//            ser << "segment: "<< "#000000" << ", ";//black
//            ser << a.from->toString() << ", " << a.to->toString();
//        }
//        return ser.str();
//    }

};



#endif
