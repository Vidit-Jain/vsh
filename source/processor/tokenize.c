#include "tokenize.h"
void expandArgs(TokenArray *tokens) {
	for (int i = 1; i < tokens->argCount; i++) {
		tokens->args[i] = expandPath(tokens->args[i]);
	}
}
void tokenizeCommand(TokenArray *tokens, String input) {
	char *currentToken;
	currentToken = strtok(input.str, " \t");
	tokens->argCount = 0;
	while (currentToken != NULL) {
		tokens->args[tokens->argCount] = initString(currentToken);
		currentToken = strtok(NULL, " \t");
		tokens->argCount++;
	}
	tokens->args[tokens->argCount] = NULL;
	expandArgs(tokens);
}
