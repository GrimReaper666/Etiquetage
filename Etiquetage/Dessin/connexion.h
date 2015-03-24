#ifndef CONNEXION_H
#define CONNEXION_H
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

#ifdef  __unix__

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <errno.h>


    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define WSAGetLastError() errno
    #define SD_BOTH 2
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;

#else

    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib") // sp�cifique � VISUAL C++
    #if (_MSC_VER == 1800)
        #define strdup _strdup
    #endif

#endif



/**
* @brief The Connexion class
* Cette classe est charg�e d'�tablire une connexion avec un serveur distant
* Cette classe charge une seule fois les dll Windows pour toutes les instances, cette partie est donc un singleton.
* De plus elle est compilable et fonctionnelle sous windows et unix(linux / mac compris) car la portabilit� c'est la vie.
*/
class Connexion{
	
private:

    SOCKET _sock;

    static bool initialisee;
	
    static void init();

public:
	
    Connexion(const std::string &ip, int host);
	void envoyer(const char *)const;
    int recevoir()const;
	~Connexion();

};

#endif
