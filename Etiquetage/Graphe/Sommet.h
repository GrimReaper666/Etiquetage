#pragma once

#include <sstream>
#include <string>
#include "GElement.h"

using namespace std;



/**
Sommet d'un graphe en général
v est l'information associée au sommet : elle dépend de l'application du graphe
*/
template <class VertexType>
class Sommet : public GElement{

public:

    int degre;
    VertexType valeur;

    Sommet(const int clef, const VertexType& v) : GElement(clef), degre(0), valeur(v) {}


    operator string () const{

        ostringstream oss;

        oss << "Sommet(" << endl;
        oss << GElement::operator string() << endl;
        oss << "degré = " << degre << endl;
        oss << "v = " << valeur << endl;
        oss << ")";
        return oss.str();
    }


    bool operator ==(const Sommet &s)const{
        return degre == s.degre && valeur == s.valeur;
    }

};


template <class VertexType>
ostream& operator<<(ostream& os, const Sommet<VertexType>& sommet)
{
    return os << (string) sommet;
}



