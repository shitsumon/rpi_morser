#include "client_socket.h"

/*static function prototypes*/
static int  createSocket(void);
static void initSocket(char* pIP);
static int  connectSocket(void);

/**
 * @brief createSocket
 * @return
 */
static int createSocket(void){
    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(client_fd < 0){
        printf("Error while creating client socket: %d - %s\n!", errno, strerror(errno));
        return -1;
    }

    return 0;
}

/**
 * @brief initSocket
 */
static void initSocket(char* pIP){
    memset(&client_socket, 0, sizeof(client_socket));
    client_socket.sin_family    = AF_INET;
    client_socket.sin_port      = htons(SERVERPORT);

    if(pIP == NULL)
        client_socket.sin_addr.s_addr  = inet_addr(DEFAULT_SERVERIP);
    else
        client_socket.sin_addr.s_addr  = inet_addr(pIP);
}

/**
 * @brief connectSocket
 * @return
 */
static int connectSocket(void){
    int ret = connect(client_fd, (struct sockaddr*) &client_socket, sizeof(client_socket));

    if( ret < 0 ){
        printf("Error while connecting client socket: %d - %s\n!", errno, strerror(errno));
        return -1;
    }

    return 0;
}

/**
 * @brief connectToServer
 * @param pIP
 * @return
 */
int connectToServer(char* pIP){
    printf("Creating client socket...");
    if(createSocket()){
        return -1;
    }
    printf("done!\n");

    printf("Initializing client socket...");
    initSocket(pIP);
    printf("done!\n");

    printf("Connecting to server...");
    if(connectSocket() == -1){
        return -1;
    }
    printf("done!\n");

    return 0;
}

/**
 * @brief sendMsgToServer
 * @param pMsg
 * @return
 */
int sendMsgToServer(char* pMsg){

    int char_cnt = 0;
    int ret      = 0;

    while(*pMsg != '\0'){
        ++char_cnt;
        ret = write(client_fd, &*(++pMsg), 1);

        if(ret < 0){
            printf("Error while connecting client socket: %d - %s\n!", errno, strerror(errno));
            close(client_fd);
            return -1;
        }
    }

    close(client_fd);
    return 0;
}
