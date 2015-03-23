#include <iostream>
#include <fstream>
#include "Graphe/Graphe.h"
#include "Outils/tools.h"

using namespace std;

void baptiste(){



    Graphe g("lol");
    g.add_sommet(Sommet("source", 0, 0));
    g.add_sommet(Sommet("B", 10, 12));
    g.add_sommet(Sommet("C", 15, 25));
    g.add_sommet(Sommet("D", 5, 15));
    g.add_sommet(Sommet("E", 30, 36));
    g.add_sommet(Sommet("F", 42, 47));
    g.add_sommet(Sommet("G", 32, 41));
    g.add_sommet(Sommet("H", 42, 58));
    g.add_sommet(Sommet("I", 50, 58));
    g.add_sommet(Sommet("puit",50,68));



    g.add_arete("source","B", 4, 7);
    g.add_arete("source","C", 18, 20);
    g.add_arete("source","D", 14, 10);
    g.add_arete("source","E", 20, 6);
    g.add_arete("source","F", 17, 12);
    g.add_arete("source","G", 20, 6);
    g.add_arete("source","H", 12, 1);
    g.add_arete("source","I", 8, 11);


    g.add_arete("B","E",20, 6);
    g.add_arete("B","F",12, 1);
    g.add_arete("B","G",8, 11);
    g.add_arete("B","H",19, 1);
    g.add_arete("B","I",15, 19);
    g.add_arete("B","puit",14, 10);

    g.add_arete("C","E", 20, 6);
    g.add_arete("C","F", 12, 1);
    g.add_arete("C","G", 8, 11);
    g.add_arete("C","H", 19, 1);
    g.add_arete("C","I", 1, 4);
    g.add_arete("C","puit", 17, 6);

    g.add_arete("D","E", 20, 6);
    g.add_arete("D","F", 12, 1);
    g.add_arete("D","G", 8, 11);
    g.add_arete("D","H", 19, 1);
    g.add_arete("D","I", 1, 4);
    g.add_arete("D","puit", 17, 6);

    g.add_arete("E","F", 1, 6);
    g.add_arete("E","H", 16, 5);
    g.add_arete("E","I", 11, 17);
    g.add_arete("E","puit", 8, 8);

    g.add_arete("F","H", 6, 1);
    g.add_arete("F","I", 12, 1);
    g.add_arete("F","puit", 16, 17);

    g.add_arete("G","puit", 8, 8);

    g.add_arete("H","puit", 4, 19);

    g.add_arete("I","puit", 6, 16);


    vector<Arete> lol =  g.correction_etiquette("source","puit",&choisir,&pareto);
    for(Arete a : lol){
        cout << a << endl;
    }

}

void jonathan(){

    Graphe g("lol");
    g.add_sommet(Sommet("source", 0, 0));
    g.add_sommet(Sommet("B", 10, 12));
    g.add_sommet(Sommet("C", 15, 25));
    g.add_sommet(Sommet("D", 5, 15));
    g.add_sommet(Sommet("E", 30, 36));
    g.add_sommet(Sommet("F", 42, 47));
    g.add_sommet(Sommet("G", 32, 41));
    g.add_sommet(Sommet("H", 42, 58));
    g.add_sommet(Sommet("I", 50, 58));
    g.add_sommet(Sommet("puit",50,68));



    g.add_arete("source","B", 4, 7);
    g.add_arete("source","C", 18, 20);
    g.add_arete("source","D", 14, 10);
    g.add_arete("source","E", 20, 6);
    g.add_arete("source","F", 17, 12);
    g.add_arete("source","G", 20, 6);
    g.add_arete("source","H", 12, 1);
    g.add_arete("source","I", 8, 11);


    g.add_arete("B","E",20, 6);
    g.add_arete("B","F",12, 1);
    g.add_arete("B","G",8, 11);
    g.add_arete("B","H",19, 1);
    g.add_arete("B","I",15, 19);
    g.add_arete("B","puit",14, 10);

    g.add_arete("C","E", 20, 6);
    g.add_arete("C","F", 12, 1);
    g.add_arete("C","G", 8, 11);
    g.add_arete("C","H", 19, 1);
    g.add_arete("C","I", 1, 4);
    g.add_arete("C","puit", 17, 6);

    g.add_arete("D","E", 20, 6);
    g.add_arete("D","F", 12, 1);
    g.add_arete("D","G", 8, 11);
    g.add_arete("D","H", 19, 1);
    g.add_arete("D","I", 1, 4);
    g.add_arete("D","puit", 17, 6);

    g.add_arete("E","F", 1, 6);
    g.add_arete("E","H", 16, 5);
    g.add_arete("E","I", 11, 17);
    g.add_arete("E","puit", 8, 8);

    g.add_arete("F","H", 6, 1);
    g.add_arete("F","I", 12, 1);
    g.add_arete("F","puit", 16, 17);

    g.add_arete("G","puit", 8, 8);

    g.add_arete("H","puit", 4, 19);

    g.add_arete("I","puit", 6, 16);





    //Test affichage contenu de G
//    cout << (string) g;
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
    cout << "-------------------------------" << endl;
    cout << endl << G << endl;
    cout << "-------------------------------" << endl;
    cout << "-------------------------------" << endl;
    cout << endl << (string) G << endl;



}


void tuto_io_graphe(){
    //Lecture d'un graphe depuis un fichier
    Graphe G("LOL2");
    fstream f;
    f.open("Data/data_VRPTW_10.gpr", ios_base::in);
    if(f.is_open()){
        f >> G;
        f.close();
    }
    else
        cout << "open fail" << endl;

    //Affichage d'un graphe
    cout << "-------------------------------" << endl;
    cout << "-------------------------------" << endl;
    cout << G << endl;          //format du prof condencé
    cout << "-------------------------------" << endl;
    cout << "-------------------------------" << endl;
    cout << (string) G << endl; //format des operator string()

    //Sauvegarde d'un graphe dans un fichier
    //... I'm working on...
    //pareil pour la déclaration du graphe à chargé depuis un fichier,
    //j'peux le faire après s'il faut.
    //J'te donne déjà ça comme ça tu peux charger les graphes
    //Si tu recèles un bug dit moi.
}

int main(){

//    baptiste();
//    jonathan();

    tuto_io_graphe();





    return 0;
}

