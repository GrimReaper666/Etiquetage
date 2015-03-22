#ifndef GRAPHE_H
#define GRAPHE_H

#include <string>
#include <vector>
#include "Arete.h"
#include "Sommet.h"
#include "../Outils/exception.h"

using namespace std;



template <class ArcType, class VertexType>
class Graphe{

protected:
    int prochaineClef;

public:
    vector<Sommet<VertexType> > lSommets;
    vector<Arete<ArcType, VertexType> > lAretes;

    Graphe():prochaineClef(0){}

    virtual ~Graphe(){}

    int nombreSommets() const;
    int nombreAretes() const;

    Sommet<VertexType> creeSommet(const VertexType& info);

    /**
     * crée une arête joignant les 2 sommets debut et fin
     *
     * * met à jour les champs degré de debut et de fin
     * */
    Arete<ArcType, VertexType> creeArete(Sommet<VertexType> debut, Sommet<VertexType> fin, const ArcType& info);

    /**
    recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
    */
    vector< pair<Sommet<VertexType>, Arete<ArcType, VertexType> > > adjacences(const Sommet<VertexType> &sommet) const;


    operator string() const;

    /**
     * cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
     *
     * DONNEES : s1 et s2 deux sommets quelconques du graphe
     * RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
     * */
    Arete<ArcType, VertexType>* getAreteParSommets(const Sommet<VertexType>& s1, const Sommet<VertexType>& s2) const;

};


/**
 * crée un sommet isolé
 **/
template <class ArcType, class VertexType>
Sommet<VertexType> Graphe<ArcType, VertexType>::creeSommet(const VertexType& info)
{
    Sommet<VertexType> sommetCree(prochaineClef++, info);
    lSommets(sommetCree);
    return sommetCree;
}


/**
 * crée une arête joignant les 2 sommets debut et fin
 * met à jour les champs degre de debut et de fin
 **/
template <class ArcType, class VertexType>
Arete<ArcType, VertexType> Graphe<ArcType, VertexType>::creeArete(Sommet<VertexType> debut, Sommet<VertexType> fin, const ArcType& info){

    Arete<ArcType, VertexType> nouvelleArete;

    // ici tester que les 2 sommets sont bien existants dans le graphe
    if(! vector< Sommet<VertexType> >::appartient(debut, lSommets) )
        throw Exception("début d'arête non défini");
    if(! vector< Sommet<VertexType> >::appartient(fin, lSommets))
        throw Exception("fin d'arête non définie");

    nouvelleArete = new Arete<ArcType, VertexType>(prochaineClef++, debut, fin, info);
    lAretes = new vector< Arete<ArcType, VertexType> >(nouvelleArete, lAretes);
    debut->degre++;
    fin->degre++;

    return nouvelleArete;
}


template <class ArcType, class VertexType>
int Graphe<ArcType, VertexType>::nombreSommets() const{
    return vector< Sommet<VertexType> >::taille(lSommets);
}

template <class ArcType, class VertexType>
int Graphe<ArcType, VertexType>::nombreAretes() const{
    return vector< Arete<ArcType,VertexType> >::taille(lAretes);
}

template <class ArcType, class VertexType>
Graphe<ArcType, VertexType>::operator string() const{
    ostringstream oss;
    oss << "Graphe( \n";
    oss << "prochaine clef = " << this->prochaineClef << endl;
    oss << "nombre de sommets = " << this->nombreSommets() << "\n";
    oss << vector<Sommet<VertexType> >::toString(lSommets, "", "\n", "");
    oss << "nombre d'arêtes = " << this->nombreAretes() << "\n";
    oss << vector<Arete<ArcType,VertexType> >::toString(lAretes, "", "\n", "");
    oss << ")";
    return oss.str();
}

template <class ArcType, class VertexType>
ostream& operator<<(ostream& os, const Graphe<ArcType, VertexType>& gr){
    return os << (string) gr;
}


/**
 * cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
 *
 * DONNEES : s1 et s2 deux sommets quelconques du graphe
 * RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
 *
 * */
template <class ArcType, class VertexType>
Arete<ArcType, VertexType>* Graphe<ArcType, VertexType>::getAreteParSommets(const Sommet<VertexType>& s1, const Sommet<VertexType>& s2) const{

    for(Arete<ArcType, VertexType>  l : lAretes)
        if(l->v->estEgal(s1,s2))
           return l->v;

    return NULL;
}


/**
recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
*/
template <class ArcType, class VertexType>
vector< pair<Sommet<VertexType>, Arete<ArcType, VertexType> > > Graphe<ArcType, VertexType>::adjacences(const Sommet<VertexType>& sommet) const{
    const vector<Arete<ArcType, VertexType> >* l;

    vector< pair<Sommet<VertexType>*, Arete<ArcType, VertexType>*> >* r;

    for(l=lAretes, r=NULL ; l ; l=l->s){
        if(sommet == l->v->debut)
            r = new vector< pair<Sommet<VertexType>*, Arete<ArcType, VertexType>*> > (new pair<Sommet<VertexType>*, Arete<ArcType, VertexType>*> (l->v->fin, l->v), r);
        else if( sommet == l->v->fin)
           r = new vector< pair<Sommet<VertexType>*, Arete<ArcType, VertexType>*> > (new pair<Sommet<VertexType>*, Arete<ArcType, VertexType>*> (l->v->debut, l->v), r);
    }
    return r;
}


#endif


