#ifndef ARETE_H
#define ARETE_H
#include "sommet.h"
class Arete{


public:

    Sommet* from, *to;
    double cost, resources;

//    Arete(Sommet *from, Sommet *to, const double & cost):
//        from(from), to(to), cost(cost){}
    Arete(Sommet *from, Sommet *to, const double & cost):
        from(from), to(to), cost(cost), resources(0.0){}

    Arete(Sommet *from, Sommet *to, const double & cost, const double& resources):
        from(from), to(to), cost(cost), resources(resources){}


};

#endif
