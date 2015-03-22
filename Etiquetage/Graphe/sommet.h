#ifndef SOMMET_H
#define SOMMET_H
#include "etiquette.h"
#include <cfloat>
#include <string>
#include <vector>


using std::string;
using std::vector;
class Sommet{

public:

    vector<Etiquette*> tags;
    string name;

    Sommet(const string &name):
        name(name){}


    void add_tag(const Etiquette &e){
        tags.push_back(new Etiquette(e));
    }

    double best() const{
        double best = DBL_MAX;
        for(Etiquette* e : tags){
            if(e->cost < best){
                best = e->cost;
            }
        }
        return best;
    }

    virtual ~Sommet(){
        for(Etiquette* e: tags){
            delete e;
        }
    }

    bool operator==(const Sommet &s){
        return s.name == name;
    }

};

#endif
