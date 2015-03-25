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
    double min_resource,max_resource;
    Etiquette* best;


    Sommet():
        Sommet("default_name")
        {}


    Sommet(const string &name):
        Sommet(name,0,0)
        {}

    Sommet(const string &name, const double min, const double max):
        name(name),
        min_resource(min),
        max_resource(max),
        best(NULL)
        {}


    inline void add_tag(const Etiquette &e){
        tags.push_back(new Etiquette(e));
        if(best == NULL or best->cost > e.cost){
            best = tags.back();
        }
    }

    inline void add_default_tag(){
        tags.push_back(new Etiquette(NULL,this,0,0));
        best = tags.front();
    }
/*
    bool operator ==(const Sommet &s)const{
        return s.name == name;
    }
*/

    operator string () const{
       std::ostringstream oss;
       oss << "sommet (" << endl;
       oss << "name = " << name << endl;
       oss << "Tags = (" << endl;
       for(Etiquette* e : tags){
           oss << (string) *e << endl;
       }
       oss << "))";
       return oss.str();
   }

    virtual ~Sommet(){
        for(Etiquette* e: tags){
            delete e;
        }
    }


    string toString() const{
        std::ostringstream oss;
        oss << (this->min_resource*8-300) << ", " << (this->max_resource*6-300);
        return oss.str();
    }


};

#endif
