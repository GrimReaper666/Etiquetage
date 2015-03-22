#include <iostream>
#include <fstream>
#include "Graphe/graphe.h"
#include "Outils/tools.h"

using namespace std;

void baptiste(){

    Graphe g("lol");
    g.add_sommet(Sommet("A",0,0));
    g.add_sommet(Sommet("B",5,15));
    g.add_sommet(Sommet("C",15,25));
    g.add_sommet(Sommet("D",10,12));
    g.add_sommet(Sommet("E",30,36));
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

}

void jonathan(){
    Graphe g("lol");
    g.add_sommet(Sommet("A",0,0));
    g.add_sommet(Sommet("B",5,15));
    g.add_sommet(Sommet("C",15,25));
    g.add_sommet(Sommet("D",10,12));
    g.add_sommet(Sommet("E",30,36));
    g.add_arete("A","B", 5, 7);
    g.add_arete("B","C",10, 10);
    g.add_arete("D","E", 3, 5);
    g.add_arete("A","C",7, 3);
    g.add_arete("B","D",4, 11);
    g.add_arete("C","D",5, 9);
    g.add_arete("C","E",9, 13);



    //Test affichage contenu de G
    cout << g;//<=> cout << (string) g;
    cout << "-------------------------------" << endl;

    //Test enregistrement de G dans un fichier
    fstream f;
    f.open("testDeSortie.grp", ios_base::out);
    f << g;
    f.close();
    cout << "-------------------------------" << endl;

    //Test de lecture d'un graphe depuis un fichier
    f.open("testDeSortie.grp", ios_base::in);
    f >> g;
    f.close();
    cout << "-------------------------------" << endl;



}

int main(){

    baptiste();
//    jonathan();

    cout << "Hello World!" << endl;





    return 0;
}

