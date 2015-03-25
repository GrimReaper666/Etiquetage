#ifndef TOOLS
#define TOOLS
#include <vector>
#include <cfloat>
#include "../Graphe/etiquette.h"
#include "../Graphe/sommet.h"
#include "../Graphe/Graphe.h"
using std::vector;
using std::cout;
using std::endl;


/**
 * @brief pareto
 * @param list
 * @return la liste des sommets non dominés dans le même ordre que celle passé en param
 */
inline void pareto(vector<Etiquette*> &list){

    vector<Etiquette*>::iterator prem = list.begin(), sec;
    while(prem != list.end()){
        sec = prem + 1;
        while(sec != list.end()){
            if((*prem)->domine(**sec)){
                delete *sec;
                list.erase(sec);
            }
            else if((*sec)->domine(**prem)){
                delete *prem;
                list.erase(prem);
                sec = prem+1;
            }
            else{
                sec++;
            }
        }
        prem++;
    }

    /*
    vector<Etiquette*> ret, dominees;
    //création de la liste des étiquettes dominées
    for(auto e = list.begin(); e != list.end() ; e++){
        for(auto e2 = e+1; e2 != list.end() ; e2++){
            if((*e)->domine(**e2)){
                dominees.push_back(*e2);
            }
            else if((*e2)->domine(**e)){
                dominees.push_back(*e);
            }
        }
    }



    for(auto e = list.begin() ; e != list.end() ;){
        if(std::find(dominees.begin(),dominees.end(),*e) == dominees.end()){
            ret.push_back(*e);
            e++;
        }
        else{
            delete *e;

        }
    }
    /*
    for(Etiquette* e : list){
        if(std::find(dominees.begin(),dominees.end(),e) == dominees.end()){
            ret.push_back(e);
        }
        else{
            delete e;
        }
    }
     */

   // return ret;
}

//etc...
//fonction choisir variante 1
inline Sommet* choisir_tete_liste(vector<Sommet*> &list){
    Sommet* ret = list.front();
    list.erase(list.begin());
    return ret;
}



//fonction choisir variante 2
 inline Sommet* choisir_cout_min(vector<Sommet*> &list){
    double cost{DBL_MAX};
    Sommet* best;
    size_t pos = 0, i = 0;
    for(Sommet* s : list){
        if(s->best){
            if(s->best->cost < cost){
                best = s;
                cost = s->best->cost;
                pos = i;
            }
        }
        i++;
    }
    list.erase(list.begin()+pos);
    return best;
}
//etc






#endif // TOOLS

