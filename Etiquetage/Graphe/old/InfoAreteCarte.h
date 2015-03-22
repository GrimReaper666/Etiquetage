#pragma once

#include <string>
#include <ostream>
#include <sstream>

using std::string;
using std::ostream;
using std::ostringstream;
using std::endl;



/**
Information associée à une arête  (segment rectiligne) joignant 2 lieux d'une carte routière.

On ne stocke que le côut de l'arête, c-à-d sa longueur
*/
class InfoAreteCarte
{
public:
    double cout;

    InfoAreteCarte(const double& cout) : cout(cout) {}

    operator string() const;
};

ostream& operator<<(ostream& os, const InfoAreteCarte& infoAreteCarte);


