#ifndef ETIQUETTE
#define ETIQUETTE

#include <string>
#include <sstream>

using std::ostringstream;
using std::string;
using std::endl;



class Sommet;
/**
 * @brief The Etiquette class
 * Cette classe représente une étiquette attachée à un sommet.
 */
class Etiquette{

public:
    const Etiquette* from;
    const Sommet* to;
    double cost, resources;

    /**
     * @brief Etiquette
     * @param e
     */
    Etiquette(const Etiquette &e):
        from(e.from),to(e.to),cost(e.cost),resources(e.resources){}

    /**
     * @brief Etiquette
     * @param from
     * @param to
     * @param cost
     * @param resources
     */
    Etiquette(const Etiquette* from, const Sommet *to,const double &cost, const double &resources):
        from(from),to(to), cost(cost),resources(resources){}


    /**
     * @brief Etiquette
     */
    Etiquette():
        from(NULL), to(NULL), cost(0),resources(0){}

    /**
     * @brief domine
     * Vérifie si le cette étiquette domine celle passée en paramêtre.
     * @param e
     * @return
     */
    bool domine(const Etiquette &e){
        return (    (cost < e.cost and resources <= e.resources)
                or  (cost == e.cost and resources < e.resources)      );
    }

    ~Etiquette(){}
/*
    bool operator ==(const Etiquette &e)const{
        return from == e.from and to == e.to and cost == e.cost and resources == e.resources;
    }

    bool operator !=(const Etiquette &e)const{
        return ! (*this==e);
    }
*/
    /**
     * @brief operator string
     */
    operator string () const{
       std::ostringstream oss;
       /*
       oss << "ETIQUETTE (" << endl;
       oss << "From: " << ( (from)?(string)(*from):"aucun") << endl;
    //   oss <<  "\tTo: " << ((string) (*to)) <<endl;
    */
       oss << "Cost = " << cost << endl;
       oss << "Resources = " << resources << endl;
      // oss << ")";
       return oss.str();
   }
};



#endif // ETIQUETTE

