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
#include "etiquette.h"

using std::unordered_map;
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



class Graphe{

public:
    vector<Sommet*> sommets;
    vector<Arete> aretes;
    string name;

    Graphe(const string &s):
        name(s){}

    void add_sommet(const Sommet &s){
        if( find_sommet(s.name) != NULL){
         throw Exception("sommet déjà existant");
        }
        sommets.push_back(new Sommet(s));
    }

    void add_arete(const Arete &a){
        aretes.push_back(a);
    }

    void add_arete(const string &from, const string &to, const double cost, const double resource){
        add_arete(Arete(get_sommet(from),get_sommet(to),cost,resource));

    }


    virtual ~Graphe(){
        for(Sommet* s: sommets){
            delete s;
        }
    }

    Sommet* find_sommet(const string &name){
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
    Sommet* find_sommet(const Sommet &s){
        return find_sommet(s.name);
    }

    /**
     * @brief get_sommet
     * @param name
     * @return le sommet dans le graphe ayant le même nom, s'il n'existe pas lève une exception
     */
    Sommet* get_sommet(const string &name){
        Sommet* s(find_sommet(name));
        if(s == NULL){
            throw Exception("le sommet " + name + " n'existe pas dans le graphe");
        }
        return s;
    }

    vector<Arete> correction_etiquette(const string &from, const string &to,Sommet* choisir(const vector<Sommet*> &list), vector<Etiquette*> pareto(const vector<Etiquette*> &list) ){
        Sommet* f(get_sommet(from)) , *t(get_sommet(to));
        return correction_etiquette(*f,*t,choisir,pareto);
    }


    unordered_map<Sommet*, vector<Sommet*> >* make_successor(){
        unordered_map< Sommet*, vector<Sommet*> >* ret = new unordered_map<Sommet*, vector<Sommet*> >();
        for(Arete a :aretes){
            if(ret->find(a.from) != ret->end()){
                (*ret)[a.from].push_back(a.to);
            }
            else{
                (*ret).insert(pair<Sommet*, vector<Sommet* > >(a.from, vector<Sommet*>() ));
                (*ret)[a.from].push_back(a.to);
            }
        }
        return ret;
    }



    vector<Arete> shortest_path(const Sommet *from, const Sommet *to){
        //TODO: variantes
        vector<Arete> path;
        const Etiquette* best = to->tags[0];
        for(Etiquette* e : to->tags){
            if(e->domine(*best)){
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

    vector<Arete> correction_etiquette(const Sommet &from, const Sommet &to,Sommet* choisir(const vector<Sommet*> &list), vector<Etiquette*> pareto(const vector<Etiquette*> &list) ){

        if(sommets.size() > 0){
            Sommet* source(find_sommet(from)), *puit(find_sommet(to));
            //crée les successeurs:
            unordered_map< Sommet* , vector<Sommet*> > successeurs = *make_successor();
            //On réinitialise les tags
            for(Sommet* s: sommets){
                s->tags = vector<Etiquette*>();
            }
            vector<Sommet*> list;
            list.push_back(source);

            Sommet* xi = new Sommet();
            source->add_default_tag();
            while(list.size() > 0){
                xi = choisir(list);
                //supprime xi de list
                int i = 0;
                for(Sommet* s: list){
                    if(s == xi){
                        list.erase(list.begin() + i);
                        break;
                    }
                    i++;
                }

                for(Sommet* xj : successeurs[xi]){
                    for(Etiquette* e: xi->tags){
                        Arete tmp = get_arete(xi,xj);
                        if( e->resources + tmp.resource <= xj->best() ){
                            Etiquette e_prime =  Etiquette(e, xj, e->cost + tmp.cost, e->resources + tmp.resource);
                            xj->add_tag(e_prime);
                            Etiquette* e_prime_pointer = xj->tags.back();
                            xj->tags = pareto(xj->tags);
                            if(std::find(xj->tags.begin(),xj->tags.end(),e_prime_pointer) != xj->tags.end() ){
                                list.push_back(xj);
                            }
                        }
                    }
                }
            }

            return shortest_path(source,puit);
        }
        else{
            throw Exception("Il n'y a pas assez d'arete dans le graphe");
        }
    }



    Arete get_arete(const Sommet *from, const Sommet *to){
        for(Arete a : aretes){
            if(a.from == from and a.to == to){
                return a;
            }
        }
        throw Exception("l'arete " + from->name + " => " + to->name + " n'existe pas dans le graphe");
    }

    Arete get_arete(const string &from, const string &to){
        return get_arete(find_sommet(from),find_sommet(to));
    }


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

    static string formatDuProf(const Graphe& G){
        ostringstream oss;
//        oss << "# Graphe N = " << G.sommets.size() << " ; M = " << G.aretes.size() << endl;
//        oss << endl << "ressource 1" << endl;

        oss << endl << "sectionSommets" << endl;
        for(Sommet* s : G.sommets){
            oss << s->name << "\t" << s->min_resource << "\t" << s->max_resource << endl;
            for(Etiquette* e : s->tags){
                oss << s->name << "  " << e->cost << "  " << e->resources << endl;
            }
        }

//        oss << endl << "sources" << endl;
//        oss << "...TO DO..."<< endl;

//        oss << endl << "puits" << endl;
//        oss << "...TO DO..."<< endl;

        oss << endl << "sectionArcs" << endl;
        for(Arete a : G.aretes){
            oss << a.from->name << "\t" << a.to->name << "\t" << a.cost << "\t" << a.resource << endl;
        }

//        oss << endl << "sectionGraphes" << endl;

        return oss.str();
    }

};

//Write a graphe into a stream
//G should not be empty
ostream& operator<<(ostream& out, const Graphe& G)
{
    return out << Graphe::formatDuProf(G);
}

//Read a graphe from file
//Update G given (G should be empty)
void operator>>(fstream& in, Graphe& G)
{
    char line[256];

    while(!in.eof()){
        in.getline(line, 256);

        std::cout << line << std::endl;

        if(string(line) == string("sectionSommets")){
            do{
                in.getline(line, 256);
                if(in.eof())
                    break;
                stringstream ss;
                ss << line;
                if(ss.str().size() == 0)
                    break;
                string sname;
                double min;
                double max;
                ss >> sname;
                ss >> min;
                ss >> max;
                std::cout << "[" << ss.str().size() << "]";
                std::cout << "\t" << sname << "\t" << min << "\t" << max << endl;

                Sommet s(sname, min, max);
//                s.add_tag(Etiquette(&s, cost, resources));
                G.add_sommet(s);
            }while(true);
        }
        if(string(line) == string("sources")){
            do{
                in.getline(line, 256);
                if(in.eof())
                    break;
                stringstream ss;
                ss << line;
                if(ss.str().size() == 0)
                    break;
//                string name;
//                string cost;
//                string resources;
//                ss >> name;
//                ss >> cost;
//                ss >> resources;
//                std::cout << "[" << ss.str().size() << "]";
//                std::cout << "\t" << name << "\t" << cost << "\t" << resources << endl;
//                G.add_sommet(Sommet());
            }while(true);
        }
        if(string(line) == string("puits")){
            do{
                in.getline(line, 256);
                if(in.eof())
                    break;
                stringstream ss;
                ss << line;
                if(ss.str().size() == 0)
                    break;
//                string name;
//                string cost;
//                string resources;
//                ss >> name;
//                ss >> cost;
//                ss >> resources;
//                std::cout << "[" << ss.str().size() << "]";
//                std::cout << "\t" << name << "\t" << cost << "\t" << resources << endl;
//                G.add_sommet(Sommet());
            }while(true);
        }
        if(string(line) == string("sectionArcs")){
            do{
                in.getline(line, 256);
                if(in.eof())
                    break;
                stringstream ss;
                ss << line;
                if(ss.str().size() == 0)
                    break;
                string nameA;
                string nameS1;
                string nameS2;
                double cost;
                double resource;
                ss >> nameA;
                ss >> nameS1;
                ss >> nameS2;
                ss >> cost;
                ss >> resource;
                std::cout << "[" << ss.str().size() << "]";
                std::cout << "\t" << nameA << "\t" << nameS1 << "\t" << nameS2 << "\t" << cost << "\t" << resource << endl;

                G.add_arete(nameS1, nameS2, cost, resource);
            }while(true);
        }
//        if(string(line) == string("sectionGraphes")){
//        }
    }
}



#endif
