#include "tokenArray.h"
const unsigned int MAX_ARGS = 200;
TokenArray *newTokenArray() {
    TokenArray *tokens = (TokenArray*) malloc(sizeof(TokenArray));
    tokens->args = (String**) malloc(MAX_ARGS * sizeof(String*));
    tokens->maxSize = MAX_ARGS;
}

TokenArray *newTokenArrayCustom(unsigned int size) {
    TokenArray *tokens = (TokenArray*) malloc(sizeof(TokenArray));
    tokens->args = (String**) malloc(size * sizeof(String*));
    tokens->maxSize = size;
}
