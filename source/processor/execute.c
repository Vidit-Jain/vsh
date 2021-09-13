#include "execute.h"

unsigned int isCommand(TokenArray *tokens, String str) {
	return isEqualString(*tokens->args[0], str);
}
void executeCommand(TokenArray *tokens) {
	if (tokens->argCount == 0)
		return;
	else if (isCommand(tokens, *initString("cd"))) {
		commandCD(tokens);
	} else if (isCommand(tokens, *initString("echo"))) {
		commandEcho(tokens);
	} else if (isCommand(tokens, *initString("pwd"))) {
		commandPWD(tokens);
	} else if (isCommand(tokens, *initString("ls"))) {
		commandLS(tokens);
	} else {
		exec(tokens);
	}
}

void executeLine(TokenArray *tokens, String input) {
	char *currentCommand;
	String *parseInput = initString(input.str);
	while (
		(currentCommand = strtok_r(parseInput->str, ";", &parseInput->str))) {
		tokenizeCommand(tokens, *initString(currentCommand));
		executeCommand(tokens);
	}
}
