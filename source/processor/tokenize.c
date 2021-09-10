#include "tokenize.h"
void tokenize(TokenArray* tokens, String input) {
    char* currentToken;
    currentToken = strtok(input.str, " ");
    tokens->argCount = 0;
    while (currentToken != NULL) {
        tokens->args[tokens->argCount] = initString(currentToken);
        currentToken = strtok(NULL, " ");
        tokens->argCount++;
    }
    tokens->args[tokens->argCount] = NULL;
}
