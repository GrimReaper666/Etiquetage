#include <iostream>
#include <fstream>
#include "Graphe/graphe.h"
#include "Outils/tools.h"

using namespace std;


int main(){
    cout << "Hello World!" << endl;

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

//    vector<Arete> lol =  g.correction_etiquette("A","E",&choisir);
//    for(Arete a : lol){
//        cout << a;
//    }
    cout << "Hello World!" << endl;




    //Test affichage contenu de G
//    cout << g;//<=> cout << (string) g;
//    cout << "-------------------------------" << endl;

    //Test enregistrement de G dans un fichier
//    fstream f;
//    f.open("testDeSortie.gpr", ios_base::out);
//    f << g;
//    f.close();
//    cout << "-------------------------------" << endl;

    //Test de lecture d'un graphe depuis un fichier
    Graphe G("LOL2");
    fstream f;
    f.open("Data/data_VRPTW_10.gpr", ios_base::in);
    if(f.is_open()){
        f >> G;
        f.close();
    }
    else
        cout << "open fail" << endl;
    cout << "-------------------------------" << endl;
    cout << endl << G << endl;


    return 0;
}

