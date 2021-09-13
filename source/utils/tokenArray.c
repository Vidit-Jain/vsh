#include "tokenArray.h"
const unsigned int MAX_ARGS = 256;
TokenArray *newTokenArray() {
	TokenArray *tokens = (TokenArray *)malloc(sizeof(TokenArray));
	tokens->args = (String **)malloc(MAX_ARGS * sizeof(String *));
	tokens->maxSize = MAX_ARGS;
}

TokenArray *newTokenArrayCustom(unsigned int size) {
	TokenArray *tokens = (TokenArray *)malloc(sizeof(TokenArray));
	tokens->args = (String **)malloc(size * sizeof(String *));
	tokens->maxSize = size;
}

TokenArray *duplicateTokenArray(TokenArray *tokens) {
    TokenArray *duplicate = newTokenArrayCustom(tokens->maxSize);
    duplicate->argCount = tokens->argCount;
    for (int i = 0; i < duplicate->argCount; i++) {
        duplicate->args[i] = initString(tokens->args[i]->str);
    }
    return duplicate;
}