#ifndef ARETE_H
#define ARETE_H

#include "sommet.h"
#include <iostream>
#include <ostream>
#include <sstream>


using std::endl;

/**
 * @brief The Arete class
 * Cette classe sert à la représentation d'un Graphe.
 * Elle est définie par les deux sommets qu'elle relit, ansi qu'un coût et une ressource exprimé par des réels.
 */
class Arete{


public:

    Sommet* from, *to;
    double cost, resource;

    /**
     * @brief Arete
     * @param from Sommet de provenance
     * @param to Sommet de destination
     * @param cost Coût de déplacement
     * @param resource Ressource de déplacement
     */
    Arete(Sommet *from, Sommet *to, const double & cost, const double &resource):
        from(from), to(to), cost(cost), resource(resource){}


    /**
     * @brief operator string
     */
    operator string () const{
           std::ostringstream oss;
           oss << "Arete (" << endl;
           oss << "debut = " << from->name << endl;
           oss << "fin = " << to->name << endl;
           oss << "valeur = (" << cost << ", "<< resource << ")" << endl;
           oss << ")";
           return oss.str();
       }

    /**
     * @brief Arete
     * @param from Sommet de provenance
     * @param to Sommet de destination
     * @param cost Coût de déplacement
     */
    Arete(Sommet *from, Sommet *to, const double & cost):
        from(from), to(to), cost(cost), resource(0.0){}


    /**
     * @brief toString
     * @param rouge
     * @return
     */
    string toString(bool rouge = true)const {
        ostringstream ser;
        ser.flush();
        ser << "segment: "<< (rouge?"#ff0000":"#000000") << ", ";//black
        ser << from->toString() << ", " << to->toString();
        return ser.str();
    }

};

#endif
