#ifndef TOOLS
#define TOOLS
#include <vector>
#include "../Graphe/etiquette.h"
using std::vector;

//fonction pour mesurer le temps d'execution d'une autre fonction


//fonction pareto variant 1
vector<Etiquette*> pareto(const vector<Etiquette*> &list){
    vector<Etiquette*> ret;
    Etiquette* best = list[0];
    for(Etiquette* e : list){
        if(e->domine(*best)){
            best = e;
            ret = vector<Etiquette*>();
            ret.push_back(best);
        }
        else{
            if( ! best->domine(*e)){
                bool deja = false;
                for(Etiquette* e2 : ret){
                    if( *e2 == *e){
                        deja = true;
                        break;
                    }
                }
                if( ! deja){
                    ret.push_back(e);
                }
            }
        }
    }

  //  ret.push_back(best);
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

