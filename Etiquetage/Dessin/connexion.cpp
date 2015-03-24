#include "connexion.h"
#include "../Outils/exception.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

bool Connexion::initialisee = false;



/**
* @brief Connexion::envoyer envoie le message au serveur
* @param message le message à envoyer
* Cette méthode permet d'envoyer un message au serveur
* Il ne faut pas ajouter "\r\n" à la fin du message, la fonction s'en charge.
*/
void Connexion::envoyer(const char *message)const{
    char* temp = (char*) malloc(sizeof(char) * (strlen(message) + strlen("\r\n") +2) ); // +2 car il faut compter les \0
    strcpy(temp,message);
    strcat(temp, "\r\n");
//    char* envoie = strdup(temp);
//    int l = strlen(envoie);
    int l = strlen(temp);
    if (send(_sock, temp, l, 0) == SOCKET_ERROR){
        throw Exception("échec de l'envoi de la requête" + WSAGetLastError());
    }
//    free(envoie);
    free(temp);
}


/**
* @brief DessinManager::recevoir
* @return la réponse du serveur, 0 (il y a eu une Exception) ou 1 (tout s'est bien passé)
* Fonction à appeller après chaque envoie de message, elle vérifie que le message a bien été reçu par le serveur
*/
int Connexion::recevoir()const{
	char reponse[1];
	if (recv(_sock, reponse, 1, 0) == SOCKET_ERROR){
        throw Exception("La réception de la réponse a échoué");
	}
    cout << "reponse: " << reponse[0] << endl;
    return atoi(reponse);
}



Connexion::~Connexion(){

	if (shutdown(_sock, SD_BOTH) == SOCKET_ERROR){
		ostringstream oss;
		oss << "la coupure de connexion a échoué" << WSAGetLastError() << endl;
        cout << (oss.str().c_str());
	}

	if (closesocket(_sock)){
		ostringstream oss;
		oss << "La fermeture du socket a échoué" << WSAGetLastError() << endl;
        cout << (oss.str().c_str());

	}
	#ifdef WIN32
		WSACleanup();
	#endif
}

void Connexion::init(){

#ifdef WIN32
    if(!initialisee){
        //initialisation winsock
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 0), &wsaData)){
            throw Exception("L'initialisation a échoué");
        }
        initialisee = true;
    }

#endif
}

Connexion::Connexion(const string &ip, int host){


        init();

	//création du socket 
	int familleAdresses = AF_INET;          // IPv4
	int typeSocket = SOCK_STREAM;           // mode connecté TCP
	int protocole = IPPROTO_TCP;            // protocole. On peut aussi mettre 0 et la fct choisit le protocole en fct des 2 1ers paramètres
	_sock = socket(familleAdresses, typeSocket, protocole);
	if (_sock == INVALID_SOCKET){
		ostringstream oss;
        oss << "la création du socket a échoué : code d'Exception = " << WSAGetLastError() << endl;
        throw Exception(oss.str().c_str());
	}

	SOCKADDR_IN sockaddr; // informations concernant le serveur avec lequel on va communiquer
    sockaddr.sin_family = AF_INET;

    //initialisation de sockaddr
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(host);                 //htons() assure que le port est bien inscrit dans le format du réseau (little-endian ou big-endian)

    // connexion du client au serveur
    if (connect(_sock, (SOCKADDR *)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR){
        throw Exception("la connexion a échouée, c'est peut être dû à une mauvaise adresse ip ou un mauvais port");
    }

}
