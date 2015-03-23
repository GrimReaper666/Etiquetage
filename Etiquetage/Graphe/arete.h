#ifndef ARETE_H
#define ARETE_H
#include "sommet.h"
#include <iostream>
#include <ostream>
#include <sstream>


using std::endl;
class Arete{


public:

    Sommet* from, *to;
    double cost, resource;

    Arete(Sommet *from, Sommet *to, const double cost, const double resource):
        from(from), to(to){
        this->cost = cost;
        this->resource = resource;
    }


    //bug sur cost et resources surement car la l'initialisation à foiré
    operator string () const{
           std::ostringstream oss;
           oss << "ARETE (" << endl;
           oss << "debut = " << from->name << endl;
           oss << "fin = " << to->name << endl;
           oss << "valeur = (" << cost << ", "<< resource << ")" << endl;
           oss << ")";
           return oss.str();
       }

    Arete(Sommet *from, Sommet *to, const double cost):
        from(from), to(to), cost(cost), resource(0.0){}

    Arete(Sommet *from, Sommet *to):
        from(from), to(to){
        cost = 0.0;
        resource = 0.0;
    }




};


std::ostream& operator<<(std::ostream& os, const Arete & arete){
    return os << (string) arete;
}

#endif
