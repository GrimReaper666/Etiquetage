#pragma once

#include <string>
#include <vector>
#include "Arete.h"
#include "Sommet.h"
//#include "../InfoSommetCarte.h"
//#include "../InfoAreteCarte.h"

using namespace std;



template <class S, class T>
class Graphe
{
protected:
    int prochaineClef;

public:
    vector<Sommet<T> > lSommets; // liste de sommets
    vector<Arete<S, T> > lAretes; // liste d'arêtes

    /**
     * crée un graphe vide
     * */
    Graphe();

    /**
     * constructeur de copie obligatoire car la classe comporte une partie dynamique
     * */
    Graphe(const Graphe<S, T>& graphe);

    /**
     * opérateur = obligatoire car la classe comporte une partie dynamique
     * */
    const Graphe<S, T>& operator=(const Graphe<S, T>& graphe);

    /**
     * destructeur obligatoire car la classe comporte une partie dynamique
     * */
    ~Graphe();

    int nombreSommets() const;
    int nombreAretes() const;

    /**
     * crée un sommet isolé
     * */
    Sommet<T> creeSommet(const T& info);

    /**
     * crée une arête joignant les 2 sommets debut et fin
     *
     * * met à jour les champs degré de debut et de fin
     * */
    Arete<S, T> creeArete(Sommet<T> debut, Sommet<T> fin, const S& info);

    /**
    recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
    */
    vector< pair<Sommet<T>, Arete<S, T> > > adjacences(const Sommet<T> sommet) const;
    operator string() const;

    /**
     * cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
     *
     * DONNEES : s1 et s2 deux sommets quelconques du graphe
     * RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
     * */
    Arete<S, T>* getAreteParSommets(const Sommet<T>* s1, const Sommet<T>* s2) const;


    bool completerGraphe(const S& infoMax){
//        vector<Sommet<T> >* tmpSommets; // liste de sommets
//        vector<Sommet<T> >* tmpSommets2; // liste de sommets
//        vector<Arete<S, T> >* tmpAretes;
//        vector<Arete<S, T> >* tmpAretesSave = lAretes;
//        int nbSommets = vector<Sommet<T> >::taille(lSommets);
//        int nbAretes = vector<Arete<S, T> >::taille(lAretes);
//        cout << "Nb sommets : " << nbSommets << endl;
//        cout << "Nb aretes : " << nbAretes << endl;

//        if(nbSommets == 0)
//            return false;//graphe vide
//        if(nbAretes == (nbSommets*(nbSommets-1)) / 2)
//            return true;//graphe complet

//        Sommet<T> *A;
//        Sommet<T> *B;
//        Arete<S, T> *AB;
//        bool ok = false;

//        for(tmpSommets=this->lSommets ; tmpSommets->s ; tmpSommets=tmpSommets->s){
//            A = tmpSommets->v;
//            for(tmpSommets2=tmpSommets->s ; tmpSommets2 ; tmpSommets2=tmpSommets2->s){
//                B = tmpSommets2->v;
//                ok = false;
//                for(tmpAretes=this->lAretes ; tmpAretes ; tmpAretes=tmpAretes->s){
//                    AB = tmpAretes->v;
//                    if(AB->estEgal(A, B)){
//                        ok = true;
//                        break;
//                    }
//                    else
//                        continue;

//                }
//                if(!ok){
//                    tmpAretesSave = new vector< Arete<S, T> >(new Arete<S, T>(prochaineClef++, A, B, infoMax), tmpAretesSave);
//                    A->degre++;
//                    B->degre++;
//                }
//            }
////
//        }
////            if(tmpAretes->v->estEgal(s1,s2))
////               return tmpAretes->v;

//        cout << "Nb sommets : " << vector<Sommet<T> >::taille(lSommets) << endl;
//        cout << "Nb aretes : " << vector<Arete<S, T> >::taille(tmpAretesSave) << endl;

//        lAretes = tmpAretesSave;
        return true;
    }

//---------------------- Graphe ----------------------------------
};



/**
 * crée un graphe vide
 **/
template <class S, class T>
Graphe<S, T>::Graphe()
    : prochaineClef(0), lAretes(NULL), lSommets(NULL)
{}


/**
 * crée un sommet isolé
 **/
template <class S, class T>
Sommet<T> Graphe<S, T>::creeSommet(const T& info)
{
    Sommet<T>* sommetCree = new Sommet<T> (prochaineClef++, info);
    lSommets = new vector< Sommet<T> >(sommetCree, lSommets);

    return sommetCree;
}

/**
 * crée une arête joignant les 2 sommets debut et fin
 * met à jour les champs degre de debut et de fin
 **/
template <class S, class T>
Arete<S, T> Graphe<S, T>::creeArete(Sommet<T> debut, Sommet<T> fin, const S& info)
{
    Arete<S, T> nouvelleArete;

    // ici tester que les 2 sommets sont bien existants dans le graphe
    if(! vector< Sommet<T> >::appartient(debut, lSommets) )
        throw Erreur("début d'arête non défini");
    if(! vector< Sommet<T> >::appartient(fin, lSommets))
        throw Erreur("fin d'arête non définie");

    nouvelleArete = new Arete<S, T>(prochaineClef++, debut, fin, info);
    lAretes = new vector< Arete<S, T> >(nouvelleArete, lAretes);
    debut->degre++;
    fin->degre++;

    return nouvelleArete;
}


template <class S, class T>
int Graphe<S, T>::nombreSommets() const
{
    return vector< Sommet<T> >::taille(lSommets);
}

template <class S, class T>
int Graphe<S, T>::nombreAretes() const
{
    return vector< Arete<S,T> >::taille(lAretes);
}

template <class S, class T>
Graphe<S, T>::operator string() const
{
    ostringstream oss;
    oss << "Graphe( \n";
    oss << "prochaine clef = " << this->prochaineClef << endl;
    oss << "nombre de sommets = " << this->nombreSommets() << "\n";
    oss << vector<Sommet<T> >::toString(lSommets, "", "\n", "");
    oss << "nombre d'arêtes = " << this->nombreAretes() << "\n";
    oss << vector<Arete<S,T> >::toString(lAretes, "", "\n", "");
    oss << ")";
    return oss.str();
}

template <class S, class T>
ostream& operator<<(ostream& os, const Graphe<S, T>& gr)
{
    return os << (string) gr;
}


/**
 * cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
 *
 * DONNEES : s1 et s2 deux sommets quelconques du graphe
 * RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
 *
 * */
template <class S, class T>
Arete<S, T>* Graphe<S, T>::getAreteParSommets(const Sommet<T>* s1, const Sommet<T>* s2) const
{
    vector<Arete<S, T> >* l;

    for(l=this->lAretes ; l ; l=l->s)
        if(l->v->estEgal(s1,s2))
           return l->v;

    return NULL;
}


/**
recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
*/
template <class S, class T>
vector< pair<Sommet<T>*, Arete<S, T>*> >* Graphe<S, T>::adjacences(const Sommet<T>* sommet) const
{
    const vector<Arete<S, T> >* l;

    vector< pair<Sommet<T>*, Arete<S, T>*> >* r;

    for(l=lAretes, r=NULL ; l ; l=l->s){
        if(sommet == l->v->debut)
            r = new vector< pair<Sommet<T>*, Arete<S, T>*> > (new pair<Sommet<T>*, Arete<S, T>*> (l->v->fin, l->v), r);
        else if( sommet == l->v->fin)
           r = new vector< pair<Sommet<T>*, Arete<S, T>*> > (new pair<Sommet<T>*, Arete<S, T>*> (l->v->debut, l->v), r);
    }
    return r;
}


