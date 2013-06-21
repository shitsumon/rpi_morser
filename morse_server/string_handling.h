#ifndef STRING_HANDLING_H
#define STRING_HANDLING_H

#include "includes.h"

/**
 * @brief stripWordsFromString
 * @param sentence
 * @param wordCount
 * @return
 */
char** stripWordsFromString(char* pSentence, int *pWordCount);

/**
 * @brief freeWordList
 * @param list
 * @param count
 */
void freeWordList(char** list, int *count);

#endif // STRING_HANDLING_H
