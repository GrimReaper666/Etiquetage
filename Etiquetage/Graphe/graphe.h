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
#include <utility>
#include "Etiquette.h"

using std::unordered_map;
using std::pair;
using std::fstream;
using std::ostringstream;
using std::endl;
using std::ostream;
using std::ofstream;
using std::istream;
using std::string;



class Graphe{

public:
    vector<Sommet*> sommets;
    vector<Arete> aretes;
    string name;

    Graphe(const string &s):
        name(s){}

    void add_sommet(const Sommet &s){
        sommets.push_back(new Sommet(s));
    }

    void add_arete(const Arete &a){
        aretes.push_back(a);
    }

    void add_arete(const string &from, const string &to, const double &cost){
        add_arete(Arete(get_sommet(from),get_sommet(to),cost));

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

    Sommet* find_sommet(const Sommet &s){
        return find_sommet(s.name);
    }

    Sommet* get_sommet(const string &name){
        Sommet* s(find_sommet(name));
        if(s == NULL){
            throw Exception("le sommet " + name + " n'existe pas dans le graphe");
        }
        return s;
    }

    vector<Arete> correction_etiquette(const string &from, const string &to,Sommet* choisir(const vector<Sommet*> &) ){
        Sommet* f(get_sommet(from)) , *t(get_sommet(to));
        return correction_etiquette(*f,*t,choisir);
    }


    unordered_map<Sommet*, vector<Sommet*> >* make_successor(){
        unordered_map< Sommet*, vector<Sommet*> >* ret;
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

    vector<Arete> correction_etiquette(const Sommet &from, const Sommet &to,Sommet* choisir(const vector<Sommet*> &) ){

        vector<Arete> path;

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

            Sommet* xi;
            xi->add_tag(Etiquette());
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
                        /*
                         TODO
                        if( e->cost + tmp.cost <= xj->best() ){
                            Etiquette e_prime =  Etiquette(xi, xi,e->cost + tmp.cost);
                        }

                        */
                    }
                }
            }

        }
        return path;
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

        oss << endl << "sectionSommets" << endl;
        for(Sommet* s : sommets){
            for(Etiquette* e : s->tags){
                oss << s->name << "  " << e->cost << "  " << e->resources << endl;
            }
//            oss << s->name << endl;
        }

        oss << endl << "sources" << endl;
        oss << "...TO DO..."<< endl;

        oss << endl << "puits" << endl;
        oss << "...TO DO..."<< endl;

        oss << endl << "sectionArcs" << endl;
        for(Arete a : aretes){
            oss << a.from->name << "  " << a.to->name << "  " << endl;//a.cost << "  " << a.resources <<
        }

        oss << endl << "sectionGraphes" << endl;

        return oss.str();
    }

};

//Write a graphe into a stream
//G should not be empty
ostream& operator<<(ostream& out, const Graphe& G)
{
    return out << (string) G;
}

//Read a graphe from file
//Update G given (G should be empty)
void operator>>(fstream& in, Graphe& G)
{
    char line[256];

    while(!in.eof()){
        in.getline(line, 256);
        std::cout << line << std::endl;
    }
}



#endif
