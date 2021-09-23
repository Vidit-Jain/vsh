#include "tokenize.h"
// Replace '~' with the home path if '~' is the first character of the argument
void expandArgs(TokenArray *tokens) {
	for (int i = 1; i < tokens->argCount; i++) {
		String *expandedPath = expandPath(tokens->args[i]);
		if (tokens->args[i] != NULL)
			free(tokens->args[i]->str);
		free(tokens->args[i]);
		tokens->args[i] = expandedPath;
	}
}
// Tokenize the line of input given
void tokenizeCommand(TokenArray *tokens, char *input) {
	char *currentToken;
	currentToken = strtok(input, " \t");
	tokens->argCount = 0;
	while (currentToken != NULL) {
		if (tokens->args[tokens->argCount] != NULL)
			free(tokens->args[tokens->argCount]->str);
		free(tokens->args[tokens->argCount]);
		tokens->args[tokens->argCount] = initString(currentToken);
		currentToken = strtok(NULL, " \t");
		tokens->argCount++;
	}
	tokens->args[tokens->argCount] = NULL;
	expandArgs(tokens);
}
