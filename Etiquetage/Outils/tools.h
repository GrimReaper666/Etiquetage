#ifndef TOOLS
#define TOOLS
#include <vector>
#include <iostream>
#include <algorithm>
#include "../Graphe/etiquette.h"
using std::vector;
using std::cout;
using std::endl;
//fonction pour mesurer le temps d'execution d'une autre fonction


//fonction pareto variant 1
vector<Etiquette*> pareto(const vector<Etiquette*> &list){
    cout << "entrée : "<< list.size() << endl;
    vector<Etiquette*> ret, dominees;
    //création de la liste des étiquettes dominées
    for(auto e = list.begin(); e != list.end() ; e++){
        for(auto e2 = list.begin(); e2 != list.end() ; e2++){
            if((*e)->domine(**e2)){
                if(std::find(dominees.begin(),dominees.end(),*e2) == dominees.end()){
                    dominees.push_back(*e2);
                }
            }
        }
    }

    for(Etiquette* e : list){
        if(std::find(dominees.begin(),dominees.end(),e) == dominees.end()){
            ret.push_back(e);
        }
    }

    /*
    for(auto best = list.begin(); best != list.end() ; best++){
        tmp.clear();
        for(auto e = best; e != list.end() ; e++){
            if( (*e)->domine(**best) ){
                //si e domine best on arrete d'itérer,et on vide tmp
                tmp.clear();
                break;
            }
            if( ! (*best)->domine(**e)){
                //si e ne domine pas best et best ne domine pas e on ajoute e
                tmp.push_back(*e);
            }
        }
        auto it = tmp.begin();
        while(it != tmp.end()){
            if(std::find(ret.begin(),ret.end(),*it) == ret.end()){
                ret.push_back(*it);
            }
            it++;
        }
    }
    */
     cout << "sortie : "<< ret.size() <<endl;

    return ret;
}

//etc...
//fonction choisir variante 1
Sommet* choisir(const vector<Sommet*> &list){
    /*TODO: faire une version non débile */
    return list[0];
}

//fonction choisir variante 2

//etc


#endif // TOOLS

