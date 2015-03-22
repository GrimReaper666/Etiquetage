#ifndef ETIQUETTE
#define ETIQUETTE

class Sommet;
class Etiquette{


public:


    const Sommet* from;
    double cost, resources;

    Etiquette(const Etiquette &e):
        from(e.from),cost(e.cost),resources(e.resources){}

    Etiquette(const Sommet* from,const double &cost, const double &resources):
        from(from),cost(cost),resources(resources){}

    Etiquette():
        from(NULL),cost(0),resources(0){}

};

#endif // ETIQUETTE

