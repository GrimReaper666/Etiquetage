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


    Sommet():
        name("default_name"),
        min_resource(0),
        max_resource(0)
        {}


    Sommet(const string &name):
        name(name),
        min_resource(0),
        max_resource(0)
        {}

    Sommet(const string &name, const double min, const double max):
        name(name),
        min_resource(min),
        max_resource(max)
        {}


    void add_tag(const Etiquette &e){
        tags.push_back(new Etiquette(e));
    }

    void add_default_tag(){
        tags.push_back(new Etiquette(NULL,this,0,0));
    }

    bool operator ==(const Sommet &s)const{
        return s.name == name;
    }


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
/*
    double best() const{
        //TODO faire une var membre
        double best = DBL_MAX;
        for(Etiquette* e : tags){
            if(e->resources < best){
                best = e->resources;
            }
        }
        return best;
    }
*/
    virtual ~Sommet(){
        for(Etiquette* e: tags){
            delete e;
        }
    }


};

#endif
