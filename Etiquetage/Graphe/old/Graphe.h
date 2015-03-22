#ifndef GRAPHE_H
#define GRAPHE_H

#include <string>
#include <vector>
#include "Sommet.h"
#include "Arete.h"
#include "../Outils/exception.h"
//#include "../InfoSommetCarte.h"
//#include "../InfoAreteCarte.h"

using namespace std;



template <class ArcType, class VertexType>
class Graphe{


protected:

    int prochaineClef;

public:


    vector<Sommet<VertexType, ArcType> > lSommets;
    vector<Arete<ArcType, VertexType> > lAretes;

    Graphe():prochaineClef(0){}

    virtual ~Graphe(){}

    int nombreSommets() const;
    int nombreAretes() const;

    void creeSommet(const VertexType& info);

    /**
     * crée une arête joignant les 2 sommets debut et fin
     *
     * * met à jour les champs degré de debut et de fin
     * */
    void creeArete(const int &from,const int &to, const ArcType& info);

    /**
    recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
    */
    vector< Arete<ArcType, VertexType>  > adjacences(const Sommet<VertexType, ArcType> &sommet) const;


    operator string() const;

    /**
     * cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
     *
     * DONNEES : s1 et s2 deux sommets quelconques du graphe
     * RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
     * */
    Arete<ArcType, VertexType>* getAreteParSommets(const Sommet<VertexType, ArcType>& s1, const Sommet<VertexType, ArcType>& s2) const;


    /**
     * @brief correction_etiquette
     * @param g
     * @return le chemin contraint de cout optimal entre le sommet d'origine et celui de destination tout en respectant
     * la limite de consomation de ressource
     */
    vector< Arete< ArcType, VertexType> > correction_etiquette(){
        if(lSommets.size() > 0){
            //les listes de tag sont mises à 0
            for(Sommet<VertexType, ArcType> x : lSommets){
                x.tags = vector<Etiquette<VertexType,ArcType> >();
            }
            vector<int> list;
            list.push_back(lSommets[0].clef);

        }
        vector< Arete< ArcType, VertexType> >  path;
        return path;
    }



};






/**
 * crée un sommet isolé
 **/
template <class ArcType, class VertexType>
void Graphe<ArcType, VertexType>::creeSommet(const VertexType& info)
{
    Sommet<VertexType, ArcType> sommetCree(prochaineClef++, info);
    lSommets.push_back(sommetCree);
    return sommetCree;
}

/**
 * crée une arête joignant les 2 sommets debut et fin
 * met à jour les champs degre de debut et de fin
 **/
template <class ArcType, class VertexType>
void Graphe<ArcType, VertexType>::creeArete(const int &from,const int &to, const ArcType &info){

    // ici tester que les 2 sommets sont bien existants dans le graphe
    if( from > lSommets.size() )
        throw Exception("début d'arête non défini");
    if( to > lSommets.size() )
        throw Exception("fin d'arête non définie");


    lAretes.push_back(Arete<ArcType, VertexType>(prochaineClef++, lSommets[from], lSommets[to], info));
    lSommets[from].degre++;
    lSommets[to].degre++;

}


template <class ArcType, class VertexType>
int Graphe<ArcType, VertexType>::nombreSommets() const{
    return lSommets.size();
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
    oss << vector<Sommet<VertexType, ArcType> >::toString(lSommets, "", "\n", "");
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
Arete<ArcType, VertexType>* Graphe<ArcType, VertexType>::getAreteParSommets(const Sommet<VertexType, ArcType> &s1, const Sommet<VertexType, ArcType> &s2) const{

    for(Arete<ArcType, VertexType>  l : lAretes)
        if(l->v->estEgal(s1,s2))
           return l->v;

    return NULL;
}


/**
recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
*/
template <class ArcType, class VertexType>
vector<Arete<ArcType, VertexType> > Graphe<ArcType, VertexType>::adjacences(const Sommet<VertexType, ArcType> &sommet) const{

    vector<Arete<ArcType, VertexType> > r;

    for(Arete<ArcType,VertexType> l : lAretes){
        if(sommet == l.debut)
            r.push_back(l.debut);
        else if( sommet == l.fin)
          r.push_back(l.fin);
    }
    return r;
}


#endif


