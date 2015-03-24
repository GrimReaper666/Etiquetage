#ifndef DESSINABLE_H
#define DESSINABLE_H

#include <vector>
#include "../Graphe/Graphe.h"

using std::vector;



/**
 * @brief The Dessinable class
 * Il s'agit d'une interface décrivant le comportement que doivent avoir les classes de dessin.
 * Cette classe sers donc majoritairement à assurer l'évolutivité de l'application en indiquant
 * aux autres classes voulant dessiner les formes géometriques quelles méthodes elles doivent implémenter.
 */
class Dessinable{


public:

    virtual void dessinerAretes(const vector<Arete> &va,bool graphe = true)const = 0;
    virtual ~Dessinable(){}

};

#endif // DESSINABLE_H
