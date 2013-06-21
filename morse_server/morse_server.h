#ifndef LED_BLINKER_H
#define LED_BLINKER_H

#include "includes.h"

/**
 * @brief morse_char
 **/
typedef struct{
    char ascii_character;
    char* morse_code;
}morse_character;

morse_character morse_alphabet[36];

//defines
#define DIT_TIME    100000
#define DAH_TIME    DIT_TIME * 0x3
#define SIGN_PAUSE  DIT_TIME
#define CHAR_PAUSE  DIT_TIME * 0x3
#define WORD_PAUSE  DIT_TIME * 0x7
#define PIN         24

//prototypes
/**
 * @brief usage
 */
void usage();

/**
 * @brief testMorseAlphabet
 */
void testMorseAlphabet(void);

/**
 * @brief initAlphabet
 */
void initAlphabet(void);

/**
 * @brief printWord
 * @param word
 */
void printWord(char* word);

/**
 * @brief printSentence
 * @param sentence
 */
void printSentence(int wordcount, char** sentence);

#endif //LED_BLINKER_H
