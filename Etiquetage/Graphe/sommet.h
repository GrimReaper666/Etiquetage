#ifndef SOMMET_H
#define SOMMET_H
#include "etiquette.h"
#include <cfloat>
#include <string>
#include <vector>


using std::string;
using std::vector;

/**
 * @brief The Sommet class
 * Cette classe représente un sommet d'un graphe.
 * Elle sert à la définition d'un graphe. Elle est composée d'un nom identifiant le sommet, ainsi qu'une fenêtre représenté par deux réels, et enfin par une liste d'étiquette rattachée au sommet.
 */
class Sommet{

public:

    vector<Etiquette*> tags;
    string name;
    double min_resource,max_resource;


    /**
     * @brief Sommet
     */
    Sommet():
        name("default_name"),
        min_resource(0),
        max_resource(0)
        {}


    /**
     * @brief Sommet
     * @param name
     */
    Sommet(const string &name):
        name(name),
        min_resource(0),
        max_resource(0)
        {}

    /**
     * @brief Sommet
     * @param name
     * @param min
     * @param max
     */
    Sommet(const string &name, const double min, const double max):
        name(name),
        min_resource(min),
        max_resource(max)
        {}


    /**
     * @brief add_tag
     * Ajoute une étiquette au sommet
     * @param e
     */
    void add_tag(const Etiquette &e){
        tags.push_back(new Etiquette(e));
    }

    /**
     * @brief add_default_tag
     */
    void add_default_tag(){
        tags.push_back(new Etiquette(NULL,this,0,0));
    }

    /**
     * @brief operator ==
     * @param s
     * @return
     */
    bool operator ==(const Sommet &s)const{
        return s.name == name;
    }


    /**
     * @brief operator string
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
    /**
     * @brief ~Sommet
     */
    virtual ~Sommet(){
        for(Etiquette* e: tags){
            delete e;
        }
    }


    /**
     * @brief toString
     * @return
     */
    string toString() const{
        std::ostringstream oss;
        oss << (this->min_resource*8-300) << ", " << (this->max_resource*6-300);
        return oss.str();
    }


};

#endif
