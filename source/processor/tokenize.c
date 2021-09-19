#include "tokenize.h"
// Replace '~' with the home path if '~' is the first character of the argument
void expandArgs(TokenArray *tokens) {
	for (int i = 1; i < tokens->argCount; i++) {
		tokens->args[i] = expandPath(tokens->args[i]);
	}
}
// Tokenize the line of input given
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
