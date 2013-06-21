#include "morse_server.h"
#include "gpio_access.h"

//static function prototypes
static char* searchMorseCodeForSign(char character);
static void printLetter(char* string);
static void setLEDon(int m_sec);

/**
 * @brief usage
 */
void usage(){
    printf("Usage: ./blinker [a-z0-9]{1,}\n");
}

/**
 * @brief setLEDon
 * @param m_sec
 */
static void setLEDon(int m_sec){
    set_PIN(PIN);
    usleep(m_sec);
    unset_PIN(PIN);
}

/**
 * @brief blink
 * @param string
 */
static void printLetter(char* string){

    printf("%c -- ", string[0]);
    char* morsecode = searchMorseCodeForSign(string[0]);
    printf("%s\n", morsecode);

    while(*morsecode != '\0'){

        if(*morsecode == '*'){
            setLEDon(DIT_TIME);
        }else if(*morsecode == '+'){
            setLEDon(DAH_TIME);
        }

        ++morsecode;
        usleep(SIGN_PAUSE);
    }
}

/**
 * @brief printWord
 * @param word
 */
void printWord(char* word){

    if(word == NULL){
        printf("Null pointer!");
        return;
    }

    while(*word != '\0'){
        printLetter(word);
        ++word;
        usleep(CHAR_PAUSE);
    }
}

/**
 * @brief printSentence
 * @param sentence
 */
void printSentence(int wordcount, char** sentence){

    for(int idx = 0; idx < wordcount; ++idx){
        printWord(sentence[idx]);
        usleep(WORD_PAUSE);
    }
}

/**
 * @brief searchMorseCodeForSign
 * @param character
 * @return
 */
static char* searchMorseCodeForSign(char character){

    for(int idx = 0; idx < 36; ++idx){
        if(character == morse_alphabet[idx].ascii_character)
            return morse_alphabet[idx].morse_code;
    }

    return "";
}

/**
 * @brief testMorseAlphabet
 */
void testMorseAlphabet(void){

    for(int idx = 0; idx < 36; ++idx){
        printLetter(morse_alphabet[idx].morse_code);
    }
}

/**
 * @brief initAlphabet
 */
void initAlphabet(void){

    morse_alphabet[0] =  (morse_character){'a', "*+"};
    morse_alphabet[1] =  (morse_character){'b', "+***"};
    morse_alphabet[2] =  (morse_character){'c', "+*+*"};
    morse_alphabet[3] =  (morse_character){'d', "+**"};
    morse_alphabet[4] =  (morse_character){'e', "*"};
    morse_alphabet[5] =  (morse_character){'f', "**+*"};
    morse_alphabet[6] =  (morse_character){'g', "++*"};
    morse_alphabet[7] =  (morse_character){'h', "****"};
    morse_alphabet[8] =  (morse_character){'i', "**"};
    morse_alphabet[9] =  (morse_character){'j', "*+++"};
    morse_alphabet[10] = (morse_character){'k', "+*+"};
    morse_alphabet[11] = (morse_character){'l', "*+**"};
    morse_alphabet[12] = (morse_character){'m', "++"};
    morse_alphabet[13] = (morse_character){'n', "+*"};
    morse_alphabet[14] = (morse_character){'o', "+++"};
    morse_alphabet[15] = (morse_character){'p', "*++*"};
    morse_alphabet[16] = (morse_character){'q', "++*+"};
    morse_alphabet[17] = (morse_character){'r', "*+*"};
    morse_alphabet[18] = (morse_character){'s', "***"};
    morse_alphabet[19] = (morse_character){'t', "+"};
    morse_alphabet[20] = (morse_character){'u', "**+"};
    morse_alphabet[21] = (morse_character){'v', "***+"};
    morse_alphabet[22] = (morse_character){'w', "*++"};
    morse_alphabet[23] = (morse_character){'x', "+**+"};
    morse_alphabet[24] = (morse_character){'y', "+*++"};
    morse_alphabet[25] = (morse_character){'z', "++**"};
    morse_alphabet[26] = (morse_character){'0', "+++++"};
    morse_alphabet[27] = (morse_character){'1', "*++++"};
    morse_alphabet[28] = (morse_character){'2', "**+++"};
    morse_alphabet[29] = (morse_character){'3', "***++"};
    morse_alphabet[30] = (morse_character){'4', "****+"};
    morse_alphabet[31] = (morse_character){'5', "*****"};
    morse_alphabet[32] = (morse_character){'6', "+****"};
    morse_alphabet[33] = (morse_character){'7', "++***"};
    morse_alphabet[34] = (morse_character){'8', "+++**"};
    morse_alphabet[35] = (morse_character){'9', "++++*"};
}
