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


    g.add_arete("A","B", 5, 7);
    g.add_arete("B","C",10, 10);
    g.add_arete("D","E", 3, 5);
    g.add_arete("A","C",7, 3);
    g.add_arete("B","D",4, 11);
    g.add_arete("C","D",5, 9);
    g.add_arete("C","E",9, 13);

    vector<Arete> lol =  g.correction_etiquette("A","E",&choisir,&pareto);
    for(Arete a : lol){
        cout << a;
    }
    cout << "Hello World!" << endl;
    return 0;
}

