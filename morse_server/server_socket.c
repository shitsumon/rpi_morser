#include "server_socket.h"
#include "morse_server.h"

/*static function prototypes*/
static int closeSocket(int con_fd);
static int createServerSocket();
static void initServerSocket();
static int bindAndListenServerSocket();

/**
 * @brief createServerSocket
 * @return
 */
static int createServerSocket(){
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(listen_fd < 0){
        perror("Server socket creation failed!");
        return -1;
    }

    return 0;
}

/**
 * @brief initServerSocket
 * @return
 */
static void initServerSocket(){
    memset(&server_socket, 0, sizeof(server_socket));
    server_socket.sin_family    = AF_INET;
    server_socket.sin_port      = htons(SERVERPORT);
    server_socket.sin_addr.s_addr = inet_addr(SERVERIPADDRESS);
}

/**
 * @brief bindAndListen
 * @return
 */
static int bindAndListenServerSocket(){
    int ret = bind(listen_fd, (struct sockaddr*) &server_socket, sizeof(server_socket));

    if(ret < 0){
        perror("Binding of server socket failed!");
        return -1;
    }


    ret = listen(listen_fd, LISTENQ);

    if(ret < 0){
        perror("Start listening on server socket failed!");
        return -1;
    }

    return 0;
}

/**
 * @brief closeSocket
 * @param con_fd
 * @return
 */
static int closeSocket(int con_fd){
    int ret = close(con_fd);

    if(ret < 0){
        perror("Error while closing connection!");
        return -1;
    }

    printf("Exiting safely...!\n");
    return 0;
}

/**
 * @brief startServer
 * @return
 */
int startServer(void(*serverside_func)(char*)){

//    char* client_msg = (char*) malloc(sizeof(char) * 0);

//    if (client_msg == NULL)
//        goto BAD_EXIT;

//    char* tmp_msg = (char*) malloc(sizeof(char) * 1);

//    if (tmp_msg == NULL)
//        goto BAD_EXIT;

    char last_character;

    int string_sz = 0;

    while (1) {
        int connection_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

        if( connection_fd < 0 ){
            perror("Error while trying to establish connection");
            goto BAD_EXIT;
        }

        int pid = fork();

        if(pid == 0){

            close(listen_fd);
            char test[80];
            int ret = read(connection_fd, &test, 80);

            if(ret < 0){
                perror("Error while reading from stream!");
                goto BAD_EXIT;
            }else if(ret > 0){

                printf("Result: %s\n", test);
                serverside_func(test);
            }else{
                closeSocket(connection_fd);
                printf("nothing received!");
            }

        }else if(pid > 0){
              waitpid(pid, 0, 0);
              closeSocket(connection_fd);
        }else{
            perror("Fork failed!");
            return -1;
        }



//        do{


//            int ret = read(connection_fd, tmp_msg, 1);

//            if(ret < 0){
//                perror("Error while reading from stream!");
//                goto BAD_EXIT;
//            }

//            //End if a single 'q' was sent
//            if(*tmp_msg == '\0' && last_character == 'q' && string_sz == 1){
//                free(client_msg);
//                free(tmp_msg);
//                client_msg  = NULL;
//                tmp_msg     = NULL;
//                closeSocket(connection_fd);

//                return 0;
//            }

//            printf("Current char is: %s\n", tmp_msg);

//            last_character  = *tmp_msg;
//            char* tmp_client_msg  = (char*) realloc(client_msg, sizeof(char) * ++string_sz);

//            if(tmp_client_msg == NULL){
//                goto BAD_EXIT;
//            }

//            client_msg = tmp_client_msg;

//            strcpy(client_msg++, tmp_msg);
//        }while(*tmp_msg != '\0');

//        printf("Client sent string: %s", client_msg);

//        serverside_func(client_msg);
    }

BAD_EXIT:
//    free(client_msg);
//    free(tmp_msg);
//    client_msg  = NULL;
//    tmp_msg     = NULL;

    return -1;
}

/**
 * @brief initServer
 * @return
 */
int initServer(void){

    printf("Create server socket...");

    if(createServerSocket() == -1)
        return -1;

    printf("done!\n");
    printf("Initialize server socket...");

    initServerSocket();

    printf("done!\n");
    printf("Bind socket and start listening...");

    if(bindAndListenServerSocket() == -1)
        return -1;

    printf("done!\n");

    return 0;
}
