#include "Graphe.h"



/*
void thread_fun(Graphe &g, const Sommet *&xi, Sommet *xj, vector<Sommet *> *list, vector<Etiquette*> pareto(const vector<Etiquette*> &list), bool borne_min,mutex *lock){
    for(Etiquette* e: xi->tags){

        Arete tmp = g.get_arete(xi,xj);
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

                lock->lock();
                if(std::find(list->begin(),list->end(),xj) == list->end()){
                    list->push_back(xj);
                }
                lock->unlock();
            }

        }
    }
}
*/
