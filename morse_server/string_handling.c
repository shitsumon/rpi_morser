#include "string_handling.h"

//static function prototypes
static int appendLetter(char letter, char* word, int sizeOfWord);

/**
 * @brief stripWordsFromString
 * @param sentence
 * @param wordCount
 * @return
 */
char** stripWordsFromString(char* pSentence, int* pWordCount){

    int sizeOfRawSring    = 0; //Counter for numbers of letters in input string
    int letterCounter     = 0; //Counter for letters per word

    int*  pLettersInWords = (int*)  malloc((size_t)NULL); //List with numbers of letters per word
    char* pCurrentWord    = (char*) malloc((size_t)NULL); //Pointer which temporary holds the current word

    //traverse through string
    //to get word and letter count
    while(1){

        //fetch next letter
        char currentLetter = *pSentence;

        //if it's the end of the string
        //or a white space save number
        //of letters
        if(currentLetter == ' ' || currentLetter == '\0'){

            //One more word
            ++(*pWordCount);

            //append new numberOfLetters value
            pLettersInWords = (int*) realloc(pLettersInWords, sizeof(int) * (*pWordCount));
            pLettersInWords[*pWordCount - 1] = letterCounter;

            //set back letter counter
            letterCounter = 0;

            //stop if finish
            if(currentLetter == '\0')
                break;
        }else{
            //just another letter...
            ++letterCounter;
        }

        //increment string position
        //and overall size counter
        ++sizeOfRawSring;
        ++pSentence;
    }

    //set pointer back to start address
    pSentence -= sizeof(char) * sizeOfRawSring;

    //Init list size
    char** wordList = (char**) malloc(sizeof(char*) * (*pWordCount));

    //Init word sizes
    for(int i = 0; i < (*pWordCount); ++i){
        wordList[i] = (char*) malloc(sizeof(char) * pLettersInWords[i]);
    }

    letterCounter = 0;
    int wordIndex = 0;

    //fetch letters from string
    //and group them into words
    while(1){

        char letter = *pSentence;

        if(letter == ' ' || letter == '\0'){
            //Append termination symbol
            appendLetter('\0', pCurrentWord, letterCounter);
            //copy word into list
            strcpy(wordList[wordIndex], pCurrentWord);

            //clean up current word
            free(pCurrentWord);
            pCurrentWord = NULL;
            pCurrentWord = (char*) malloc(sizeof(char) * 0);
            letterCounter = 0;

            //End, if finish...
            if(letter == '\0')
                break;

            //...else raise word count
            ++wordIndex;
        }else{
            //if another char, raise char count
            //and reallocate to store new char
            pCurrentWord = (char*) realloc(pCurrentWord, sizeof(char) * ++letterCounter);
            pCurrentWord[letterCounter - 1] = letter;
        }

        ++pSentence;
    }

    return wordList;
}

/**
 * @brief appendLetter
 * @param sentence
 * @param word
 * @param sizeOfCurrentWord
 */
static int appendLetter(char letter, char* word, int sizeOfWord){

    word = (char*) realloc(word, sizeof(char) * sizeOfWord + 1);

    if( word == NULL ){
        return -1;
    }

    word[sizeOfWord] = letter;

    return 0;
}

/**
 * @brief freeWordList
 * @param list
 * @param count
 */
void freeWordList(char** list, int* count){

    for(int idx = 0; idx < *count; ++idx){
        free(list[idx]);
    }

    free(list);
}
