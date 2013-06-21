#include "gpio_access.h"
#include "morse_server.h"
#include "string_handling.h"
#include "server_socket.h"

//Flag defines
#define SERVER_MODE 0x01 //s
#define CLI_MODE    0x02 //c
#define DAEMON_MODE 0x04 //d
#define REPEAT_MSG  0x08 //r
#define PIN_SELECT  0x10 //p

//Helper defines
#define TRUE        1
#define FALSE       0

//Prototypes
void initBlinker(void);
int hasFlagValue(int* value, int* collection);

int main(int argc, char *argv[])
{
    int activated_flags = 0x00;

    //Stop if no arguments are given
    if(argc < 2){
        goto USAGE;
    }

    //Initialize GPIO
    if(setup_GPIO() != 0){
        printf("Initializing GPIO failed!\n");
        goto EXIT_BAD;
    }

    int     lastWasFlag = 0; //Holds flag values
    char    flag;            //Holds last handled flag

    for(int idx = 1; idx < argc; ++idx){

        if(argv[idx][0] == '-'){

            char* pCurrentArgument = argv[idx];

            while(*pCurrentArgument != '\0'){

                switch(*pCurrentArgument){
                case 's':

                    //Cannot work if cli mode was set
                    if( hasFlagValue(&CLI_MODE, &activated_flags) ){
                        printf("You cannot start the blinker in server- and in cli mode!\n");
                        goto USAGE;
                    }

                    //Set server mode
                    activated_flags |= SERVER_MODE;

                    break;
                case 'c':

                    //Cannot work if server- or daemon mode was set
                    if ( hasFlagValue(&SERVER_MODE, &activated_flags) || hasFlagValue(&DAEMON_MODE, &activated_flags) ){
                        printf("You cannot start the blinker in cli- and another mode!\n");
                        goto USAGE;
                    }

                    //set cli mode
                    activated_flags |= CLI_MODE;

                    break;
                case 'd':

                    //cannot work if cli mode was set
                    if ( hasFlagValue(&CLI_MODE, &activated_flags) ){
                        printf("You cannot start the blinker in daemon- and cli mode!\n");
                        goto USAGE;
                    }

                    //Set deamon mode
                    activated_flags |= DAEMON_MODE;

                    break;
                default:
                    goto USAGE;
                    break;
                }

                ++pCurrentArgument;
            }

            //Save last flag
            flag        = *pCurrentArgument;
            lastWasFlag = TRUE;

        }else if(argv[idx][0] != '-' && lastWasFlag){

            //Interpret Values which are required by certain flags
            switch(flag){
            case 's': //Take as IP
                break;
            case 'c': //Take as sentence to morse
                break;
            case 'd': //No arguments yet
            default:
                goto USAGE;
                break;
            }

            flag = '';
            lastWasFlag = FALSE;

        }else{ //Abort if two arguments without '-' appear in a row
            goto USAGE;
        }

    }

//    int wordcount = 0;
//    char** wordList = stripWordsFromString(argv[1], &wordcount);

//    if(wordList == NULL){
//        printf("Bad wordlist!\n");
//        goto EXIT_BAD;
//    }

//    for(int i = 0; i < wordcount; ++i)
//        printf("%s\n", wordList[i]);

//    printSentence(wordcount, wordList);

//    freeWordList(wordList, &wordcount);
    initBlinker();
    initServer();
    if( startServer(&printWord) == -1)
        goto EXIT_BAD;

    return EXIT_SUCCESS;

USAGE:
    usage();
EXIT_BAD:
    return EXIT_FAILURE;
}

/**
 * @brief initBlinker
 */
void initBlinker(void){
    init_PIN(PIN);
    initAlphabet();
}

/**
 * @brief hasFlagValue
 * @param value
 * @param collection
 * @return
 */
int hasFlagValue(int* value, int* collection){
    return collection & value != 0 ? TRUE : FALSE;
}
