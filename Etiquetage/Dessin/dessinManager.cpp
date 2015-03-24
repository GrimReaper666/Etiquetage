#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include "../Outils/exception.h"
#include "dessinManager.h"

using namespace std;




DessinManager::DessinManager(Connexion *c):
_connexion(c){}




void DessinManager::dessinerAretes(const vector<Arete> &va, bool graphe = true) const{
    for(Arete a : va){
        string message = a.toString(!graphe);
        cout << message;
        _connexion->envoyer(message.c_str());
        if( ! graphe){
            stringstream ss;
            ss << "texte: #000000, " + a.to->name + ", ";
            ss << a.to->min_resource;
            ss << ", ";
            ss << a.to->max_resource;
            message = ss.str();
            cout << message << endl;
            _connexion->envoyer(message.c_str());
            cout <<endl << message <<endl;
            if (_connexion->recevoir() != 0){
                cout << "le serveur a bien reçu le texte" << endl;
            }
            else{
                cout << "il y a eu une Exception lors de l'envoie" << endl;
            }
        }
        if (_connexion->recevoir() != 0){
            cout << "le serveur a bien reçu le segment" << endl;
        }
        else{
            cout << "il y a eu une Exception lors de l'envoie" << endl;
        }
    }
}

void DessinManager::dessinerGraphe(const Graphe& G)const{
    dessinerAretes(G.getVArete());
}





