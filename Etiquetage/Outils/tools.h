#ifndef TOOLS
#define TOOLS
#include <vector>
#include "../Graphe/etiquette.h"
using std::vector;

//fonction pour mesurer le temps d'execution d'une autre fonction


//fonction pareto variant 1
vector<Etiquette*> pareto(const vector<Etiquette*> &list){
    vector<Etiquette*> ret;
    ret.push_back(list[0]);
    return ret;
    //TODO
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

