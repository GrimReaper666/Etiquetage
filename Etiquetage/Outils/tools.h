#ifndef TOOLS
#define TOOLS
#include <vector>
#include <iostream>
#include "../Graphe/etiquette.h"
using std::vector;
using std::cout;
using std::endl;
//fonction pour mesurer le temps d'execution d'une autre fonction


//fonction pareto variant 1
vector<Etiquette*> pareto(const vector<Etiquette*> &list){
    cout << "entrée : "<< list.size() << endl;
    vector<Etiquette*> copy = vector<Etiquette*>(list);
    vector<Etiquette*> ret;
    for(vector<Etiquette*>::iterator best = copy.begin(); best != copy.end() ; best++){
        for(vector<Etiquette*>::iterator e = best; e != copy.end() ; e++){
            if(  ! (*best)->domine(**e) and ! (*e)->domine(**best)){
                ret.push_back(*e);
            }
        }
    }
    /*
    for(Etiquette* best: list){
        for(Etiquette* e : list){
            if(e->domine(*best)){
               // best = e;
                ret = vector<Etiquette*>();
                ret.push_back(best);
            }
            else{
                if( ! best->domine(*e)){
                    //TODO: vérif que ce qu'on insert n'est pas déjà dans ret
                        ret.push_back(e);
                }
            }
        }
        copy = vector<Etiquette*> (ret);
        ret = vector<Etiquette*>();
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

