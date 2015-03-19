#pragma once

#include <string>
#include <sstream>
#include <ostream>
#include "../Outils/vecteur2d.h"

using namespace std;



/**
Information associée à un sommet représentant un lieu d'une carte routière.
Un lieu est défini par un nom et par une position géographique
*/
class InfoSommetCarte{

public:

    string nom;
    Vecteur2D position;

    InfoSommetCarte(const string& nom, const Vecteur2D& position) : nom(nom), position(position) {}

    operator string() const;

};

ostream& operator<<(ostream& os, const InfoSommetCarte& infoSommetCarte);


