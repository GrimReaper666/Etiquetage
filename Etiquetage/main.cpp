#include <iostream>
#include "Graphe/graphe.h"
#include "Outils/tools.h"

using namespace std;


int main(){

    Graphe g("lol");
    g.add_sommet(Sommet("A"));
    g.add_sommet(Sommet("B"));
    g.add_sommet(Sommet("C"));
    g.add_sommet(Sommet("D"));
    g.add_sommet(Sommet("E"));

    g.add_arete("A","B", 5);
    g.add_arete("B","C",10);
    g.add_arete("D","E", 3);
    g.add_arete("A","C",7);
    g.add_arete("B","D",4);
    g.add_arete("C","D",5);
    g.add_arete("C","E",9);

    g.correction_etiquette("A","E",&choisir);
    cout << "Hello World!" << endl;
    return 0;
}

