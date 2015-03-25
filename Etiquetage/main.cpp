#include <iostream>
#include <fstream>
#include "Outils/tools.h"
#include "Outils/exception.h"
#include "Dessin/connexion.h"
#include "Dessin/dessinManager.h"
#include "Graphe/Graphe.h"
#include <time.h>

using namespace std;

//Dégeulasse mais on s'en fout <= problèmes d'inclusions multiple réglé comme ça !
std::ostream& operator<<(std::ostream& os, const Arete & arete){
    return os << (string) arete;
}
//Write a graphe into a stream
//G should not be empty
ostream& operator<<(ostream& out, const Graphe& G)
{
    return out << Graphe::formatDuProf(G);
}
//Read a graphe from file
//Update G given (G should be empty)
void operator>>(fstream& in, Graphe& G)
{
    char line[256];

    while(!in.eof()){
        in.getline(line, 256);

//        std::cout << line << std::endl;

        if(string(line) == string("sectionSommets")){
            do{
                in.getline(line, 256);
                if(in.eof())
                    break;
                stringstream ss;
                ss << line;
                if(ss.str().size() == 0)
                    break;
                string sname;
                double min;
                double max;
                ss >> sname;
                ss >> min;
                ss >> max;
//                std::cout << sname << "\t" << min << "\t" << max << endl;

                Sommet s(sname, min, max);
//                s.add_tag(Etiquette(&s, cost, resources));
                G.add_sommet(s);
            }while(true);
        }
        if(string(line) == string("sources")){
            do{
                in.getline(line, 256);
                if(in.eof())
                    break;
                stringstream ss;
                ss << line;
                if(ss.str().size() == 0)
                    break;
                //...
            }while(true);
        }
        if(string(line) == string("puits")){
            do{
                in.getline(line, 256);
                if(in.eof())
                    break;
                stringstream ss;
                ss << line;
                if(ss.str().size() == 0)
                    break;
                //...
            }while(true);
        }
        if(string(line) == string("sectionArcs")){
            do{
                in.getline(line, 256);
                if(in.eof())
                    break;
                stringstream ss;
                ss << line;
                if(ss.str().size() == 0)
                    break;
                string nameA;
                string nameS1;
                string nameS2;
                double cost;
                double resource;
                ss >> nameA;
                ss >> nameS1;
                ss >> nameS2;
                ss >> cost;
                ss >> resource;
//                std::cout << nameA << "\t" << nameS1 << "\t" << nameS2 << "\t" << cost << "\t" << resource << endl;

                G.add_arete(nameS1, nameS2, cost, resource);
            }while(true);
        }
//        if(string(line) == string("sectionGraphes")){
//        }
    }
}

clock_t get_cpu_time(){
#ifdef _WIN32
#include <windows.h>
    return GetProcessTimes() //TODO ça a l'air relou
#else
    return clock();
#endif

}


void test_perf(const string &file_name, const string &from, const string &to,unsigned int nb_iter = 20){
    Graphe g("LOL2");
    fstream f;
    f.open(file_name, ios_base::in);
    cout << "for file: " << file_name << endl;
    if(f.is_open()){
        f >> g;
        f.close();
    }
    else{
        cout << "open fails" << endl;
        exit( 0);
    }
    clock_t total = 0;
    long double moyenne = 0;
    while(moyenne == 0){
        for(unsigned int i = 0 ; i < nb_iter ; i++){
            clock_t start = get_cpu_time();
            g.correction_etiquette(from,to,&choisir_cout_min,&pareto,true);
            total+= get_cpu_time() -start;
        }
        moyenne = total/(long double)nb_iter;
    }
    cout << "une moyenne de: " << (moyenne/CLOCKS_PER_SEC)*1000 << " millisecondes " <<endl;
}

/**
 * @brief test_all rq: ne pas tous les lancer à la fois car consomme toute la ram et baisse les performances.
 */
void test_all(){



    test_perf("Data/data_VRPTW_10.gpr","s0","p0");


    test_perf("Data/data_VRPTW_10_3_2_4.gpr","i1","i10");

    // test_perf("Data/data_VRPTW_10_10_5_5_3.gpr","i1","i10");





    test_perf("Data/data_VRPTW_20.gpr","i_1","i_20");

    test_perf("Data/data_VRPTW_50_10_10_15.gpr","i1","i50");

    test_perf("Data/data_VRPTW_100_10_5_9.gpr","i1","i100");
    test_perf("Data/data_VRPTW_120_8_7_11.gpr","i1","i120");
    test_perf("Data/data_VRPTW_140_8_7_11.gpr","i1","i140");

    test_perf("Data/data_VRPTW_160_10_5_10.gpr","i1","i160");


}

void baptiste(){

   test_all();


    /*
    vector<Arete> lol =  g.correction_etiquette("i1","i160",&choisir,&pareto);
 /*   for(Etiquette* e : g.get_sommet("p0")->tags){
        cout  <<(string) (*e) <<endl;
    }

      for(Arete a : lol){
        cout << a << endl;
    }
*/


}






void jonathan(){

//    Graphe g("lol");
//    g.add_sommet(Sommet("source", 0, 0));
//    g.add_sommet(Sommet("B", 10, 12));
//    g.add_sommet(Sommet("C", 15, 25));
//    g.add_sommet(Sommet("D", 5, 15));
//    g.add_sommet(Sommet("E", 30, 36));
//    g.add_sommet(Sommet("F", 42, 47));
//    g.add_sommet(Sommet("G", 32, 41));
//    g.add_sommet(Sommet("H", 42, 58));
//    g.add_sommet(Sommet("I", 50, 58));
//    g.add_sommet(Sommet("puit",50,68));



//    g.add_arete("source","B", 4, 7);
//    g.add_arete("source","C", 18, 20);
//    g.add_arete("source","D", 14, 10);
//    g.add_arete("source","E", 20, 6);
//    g.add_arete("source","F", 17, 12);
//    g.add_arete("source","G", 20, 6);
//    g.add_arete("source","H", 12, 1);
//    g.add_arete("source","I", 8, 11);


//    g.add_arete("B","E",20, 6);
//    g.add_arete("B","F",12, 1);
//    g.add_arete("B","G",8, 11);
//    g.add_arete("B","H",19, 1);
//    g.add_arete("B","I",15, 19);
//    g.add_arete("B","puit",14, 10);

//    g.add_arete("C","E", 20, 6);
//    g.add_arete("C","F", 12, 1);
//    g.add_arete("C","G", 8, 11);
//    g.add_arete("C","H", 19, 1);
//    g.add_arete("C","I", 1, 4);
//    g.add_arete("C","puit", 17, 6);

//    g.add_arete("D","E", 20, 6);
//    g.add_arete("D","F", 12, 1);
//    g.add_arete("D","G", 8, 11);
//    g.add_arete("D","H", 19, 1);
//    g.add_arete("D","I", 1, 4);
//    g.add_arete("D","puit", 17, 6);

//    g.add_arete("E","F", 1, 6);
//    g.add_arete("E","H", 16, 5);
//    g.add_arete("E","I", 11, 17);
//    g.add_arete("E","puit", 8, 8);

//    g.add_arete("F","H", 6, 1);
//    g.add_arete("F","I", 12, 1);
//    g.add_arete("F","puit", 16, 17);

//    g.add_arete("G","puit", 8, 8);

//    g.add_arete("H","puit", 4, 19);

//    g.add_arete("I","puit", 6, 16);





    //Test affichage contenu de G
//    cout << (string) g;
//    cout << g;//<=> cout << (string) g;
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
//    cout << endl << (string) G << endl;


    //Test enregistrement de G dans un fichier
//    fstream f;
    f.open("testDeSortie.gpr", ios_base::out);
    f << G;
    f.close();
    cout << "-------------------------------" << endl;


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
    f.open("testDeSortie.gpr", ios_base::out);
    f << G;
    f.close();
    cout << "-------------------------------" << endl;
}


void connexionEtDessin(){

    //Lecture d'un graphe depuis un fichier
    Graphe G("LOL2");
    fstream f;
    f.open("Data/data_VRPTW_10.gpr", ios_base::in);
//    f.open("Data/data_VRPTW_160_10_5_10.gpr", ios_base::in);
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


    //connexion
    cout << "CouCou CONNEXION !!!" << endl;
    const string ip = "127.0.0.1";
    int port = 9111;
    try{
        Connexion connect = Connexion(ip, port);
        DessinManager dm(&connect);
//        dm.dessinerAretes(G.getVArete());//listes d'arêtes
      //  dm.dessinerGraphe(G);//graphe
        dm.dessinerAretes(G.correction_etiquette("s0","p0",&choisir_tete_liste,&pareto, true),false);
    }
    catch(Exception e){
        cout << e.message << endl;
    }

}



int main(){

    baptiste();
//    jonathan();

//    tuto_io_graphe();
//    connexionEtDessin();



    return 0;
}

/*

int main(int argc, char* argv[])
{
    string path = "Data/data_VRPTW_10.gpr";
//    string path = "Data/data_VRPTW_160_10_5_10.gpr";
    cout << endl << "\t\tPROJET RO" << endl << endl;

//Récupération du chemin du graphe à ouvrir
    if(argc == 1){
        //demande de rentrer le nom du graphe à lire
        cout << "Entrez le nom du fichier contenant le graphe a ouvrir : ";
//TODO : Décommenter le cin quand plus phase de test
//        cin >> path;
    }
    else if(argc == 2){
        //ouvrir le graphe donné en paramètre
        stringstream ss;
        ss << argv[1];
        path = ss.str();
    }

    cout << endl;
    cout << endl << "[+] Chemin vers le graphe a ouvrir :" << endl;
    cout << path << endl;


//Lecture d'un graphe depuis un fichier
    Graphe G("LOL");
    fstream f;
    f.open(path.c_str(), ios_base::in);
    if(f.is_open()){
        cout << endl << "[+] Ouverture du fichier reussi." << endl;
        f >> G;
        f.close();


//TODO
        //Calcule de l'algo
        cout << endl << "[+] Debut du calcule de chemin..." << endl;
        vector<Arete> chemin = G.correction_etiquette("s0", "p0",&choisir_cout_min,&pareto);
//        vector<Arete> chemin = G.correction_etiquette("i1", "i160",&choisir,&pareto);
        cout << "[+] Fin." << endl;
        cout << endl << "TODO - sortie timer algo TODO" << endl;
        //...


        //Affichage du chemin rendu par l'algo
        cout << endl << "[+] Chemin rendu par l'algo:" << endl;
        stringstream ss;
        for(Arete a : chemin){
            ss << a.to->name << " <- ";
        }
        ss << chemin.back().from->name << endl;
        cout << ss.str();


        //Connexion au serveur de dessin
        cout << endl << endl << "[+] Connexion au serveur de dessin : " << endl;
        const string ip = "127.0.0.1";
        cout << "\tIP = " << ip << endl;
        int port = 9111;
        cout << "\tPort = " << port << endl << endl;
        try{
            Connexion connect = Connexion(ip, port);
            DessinManager dm(&connect);
            cout << "\t[+] Connexion reussie." << endl;
            cout << "\t[+] Envoie des donnees au serveur..." << endl;
            dm.dessinerGraphe(G);//graphe
            cout << endl << "\t[+] Graphe envoye au serveur. [Noir]" << endl << endl;

            cout << "\t[+] Envoie des donnees au serveur..." << endl;
            dm.dessinerAretes(chemin, false);//chemin
            cout << "\t[+] Chemin parcouru par l'algorithme envoye au serveur. [Rouge]" << endl << endl;
        }
        catch(Exception e){
            cout << endl << e.message << endl;
        }
    }
    else
        cout << "\t[-] Fichier NON ouvert." << endl;

    return 0;
}




*/
