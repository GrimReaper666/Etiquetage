#ifndef TOOLS
#define TOOLS
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <functional>
#include "../Graphe/etiquette.h"
using std::vector;
using std::cout;
using std::endl;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::chrono::duration;
using std::chrono::duration_cast;
//fonction pour mesurer le temps d'execution d'une autre fonction
template<typename F, typename ...Args>
milliseconds execution(unsigned int nb_iter, std::function<F(Args&&...) > func,Args&&... args){
  milliseconds total = 0;
  for(unsigned int i = 0 ; i < nb_iter ; i++){
      auto start = system_clock::now();
      func(std::forward<Args>(args)...);
      auto duration = duration_cast< milliseconds>(system_clock::now() - start);
      total+= duration.count();
  }
  return total/nb_iter;
}

//fonction pareto variant 1
vector<Etiquette*> pareto(const vector<Etiquette*> &list){
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

