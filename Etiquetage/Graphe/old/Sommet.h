#pragma once

#include <sstream>
#include <string>
#include "GElement.h"
#include <vector>

using namespace std;


/**
Sommet d'un graphe en général
v est l'information associée au sommet : elle dépend de l'application du graphe
*/

template <class VertexType, class ArcCost>
class Etiquette;

template <class VertexType, class ArcCost>
class Sommet : public GElement{

public:


    int degre;
    VertexType valeur;
    vector<Etiquette<VertexType,ArcCost> > tags;

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


template <class VertexType, class ArcCost>
ostream& operator<<(ostream& os, const Sommet<VertexType, ArcCost>& sommet)
{
    return os << (string) sommet;
}



