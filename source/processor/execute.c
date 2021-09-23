#include "execute.h"

unsigned int isCommand(TokenArray *tokens, char* str) {
	return strcmp(tokens->args[0]->str, str) == 0;
}
// Checks the first command and executes the appropriate command
void executeCommand(TokenArray *tokens) {
	if (tokens->argCount == 0)
		return;
	else if (isCommand(tokens, "cd")) {
		commandCD(tokens);
	} else if (isCommand(tokens, "echo")) {
		commandEcho(tokens);
	} else if (isCommand(tokens, "pwd")) {
		commandPWD(tokens);
	} else if (isCommand(tokens, "ls")) {
		commandLS(tokens);
	} else if (isCommand(tokens, "pinfo")) {
		commandPinfo(tokens);
	} else if (isCommand(tokens, "history")) {
		commandHistory(tokens);
	} else if (isCommand(tokens, "exit")) {
		exitShell();
	} else if (isCommand(tokens, "repeat")) {
		/* If repeat is called, the first two commands are removed
		 * and the rest of the command is executed multiple times in a loop
		 */

		int repeats = commandRepeat(tokens);
		if (repeats == -1) {
			return;
		}
		TokenArray *tokenReduced = newTokenArray();
		for (int i = 2; i < tokens->argCount; i++) {
			tokenReduced->args[i - 2] = initString(tokens->args[i]->str);
		}
		tokenReduced->argCount = tokens->argCount - 2;
		for (int i = 0; i < repeats; i++) {
			TokenArray *tokenCopy = duplicateTokenArray(tokenReduced);
			executeCommand(tokenCopy);
			for (int j = 0; j < tokenCopy->maxSize; j++) {
				if (tokenCopy->args[j] != NULL) {
					free(tokenCopy->args[j]->str);
					free(tokenCopy->args[j]);
				}
			}
			free(tokenCopy);
		}
	} else {
		exec(tokens);
	}
}
// Tokenize the input by the ; to execute multiple commands.
void executeLine(TokenArray *tokens, String input) {
	char *currentCommand;
	String *parseInput = initString(input.str);
	char* tempStore = parseInput->str;
	while (
		(currentCommand = strtok_r(parseInput->str, ";", &parseInput->str))) {
		tokenizeCommand(tokens, currentCommand);
		executeCommand(tokens);
	}
	free(tempStore);
	free(parseInput);
}
