#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include "includes.h"

#define SERVERPORT             6543
#define DEFAULT_SERVERIP       "10.116.1.17"
#define LISTENQ                5

struct sockaddr_in client_socket;

int client_fd;

/*Prototypes*/
int connectToServer(char* pIP);
int sendMsgToServer(char* pMsg);

#endif // CLIENT_SOCKET_H
