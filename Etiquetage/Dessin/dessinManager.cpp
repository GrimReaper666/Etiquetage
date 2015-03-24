#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include "../Outils/exception.h"
#include "dessinManager.h"

using namespace std;




DessinManager::DessinManager(Connexion *c):
_connexion(c){}




void DessinManager::dessinerAretes(const vector<Arete> &va) const{
    for(Arete a : va){
        string message = a.toString();
        cout << message;
        _connexion->envoyer(message.c_str());

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





