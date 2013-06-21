#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "includes.h"

#define SERVERPORT             6543
#define SERVERIPADDRESS        "10.116.1.17"
#define DEFAULTSERVERIPADDRESS "10.116.1.17"
#define LISTENQ                5

struct sockaddr_in server_socket;

int listen_fd;

/*Prototypes*/
int initServer(void);
int startServer(void(*serverside_func)(char*));

#endif // SERVER_SOCKET_H
