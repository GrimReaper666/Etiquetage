#pragma once

#include <sstream>
#include <string>
#include "GElement.h"
#include "Sommet.h"

using namespace std;



/**
représente une arête d'un graphe en général.
Une arête est définie par un sommet-début et par un sommet-fin et par une information v.

On ne connait pas la nature de v à ce niveau (v pourrait contenir une couleur, une longueur, un nom, etc.)

T est la nature de l'information portée par un sommet et
S est la nature de l'information portée par une arête
*/

template <class ArcType, class VertexType>
class Arete : public GElement{


public:


    Sommet<VertexType> debut, fin;
    ArcType valeur;

    Arete(int clef, const Sommet<VertexType> &debut, const Sommet<VertexType> &fin, const ArcType &v) : GElement(clef), debut(debut), fin(fin), valeur(v) {}

    operator string () const{
        ostringstream oss;

        oss << "Arete (" << endl;
        oss << GElement::operator string() << endl;
        oss << "clef debut = " << debut->clef << endl;
        oss << "clef fin = " << fin->clef << endl;
        oss << "v = " << valeur << endl;
        oss << ")";
        return oss.str();
    }

    /**
     * @brief estEgal
     * @param s1
     * @param s2
     * @return true si l'arc est composé de s1 et s2
     */
    bool estEgal(const Sommet<VertexType>& s1, const Sommet<VertexType>& s2) const{
        return (s1 == debut and s2 == fin) or (s1 == fin and s2 == debut);
    }

};


template <class ArcType, class VertexType>
ostream& operator<<(ostream& os, const Arete<ArcType, VertexType>& arete){
    return os << (string) arete;
}


