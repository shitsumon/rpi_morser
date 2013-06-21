#include "client_socket.h"

void usage();

int main(int argc, char** argv)
{
    if(argc != 3){
        usage();
        return EXIT_FAILURE;
    }

    connectToServer(argv[1]);
    sendMsgToServer(argv[2]);

    return EXIT_SUCCESS;
}

void usage(){
    printf("./morse_client IP MORSE_MESSAGE");
}
