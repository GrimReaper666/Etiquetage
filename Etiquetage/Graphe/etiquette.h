#ifndef ETIQUETTE
#define ETIQUETTE

#include <string>
#include <sstream>
using std::ostringstream;
using std::string;
using std::endl;

class Sommet;
class Etiquette{

public:
    const Sommet* from;
    double cost, resources;

    Etiquette(const Etiquette &e):
        from(e.from),cost(e.cost),resources(e.resources){}

    Etiquette(const Sommet* from, const double cost, const double resources):
        from(from),cost(cost),resources(resources){}

    Etiquette():
        from(NULL),cost(0),resources(0){}

    bool domine(const Etiquette &e){
        return (    (cost < e.cost and resources <= e.resources)
                or  (cost <= e.cost and resources < e.resources)      );
    }

    operator string () const{
       std::ostringstream oss;
       oss << "ETIQUETTE (" << endl;
       oss << "Cost = " << cost << endl;
       oss << "Resources = " << resources << endl;
       oss << ")";
       return oss.str();
   }
};

#endif // ETIQUETTE

