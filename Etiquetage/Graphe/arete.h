#ifndef ARETE_H
#define ARETE_H
#include "sommet.h"
class Arete{


public:

    Sommet* from, *to;
    double cost;

    Arete(Sommet *from, Sommet *to, const double & cost):
        from(from), to(to), cost(cost){}


};

#endif
