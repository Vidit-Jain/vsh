#include "execute.h"
#include "../commands/pinfo.h"

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
	} else if (isCommand(tokens, *initString("pinfo"))) {
		commandPinfo(tokens);
	} else if (isCommand(tokens, *initString("repeat"))) {
		int repeats = commandRepeat(tokens);
		TokenArray *tokenReduced = newTokenArray();
		for (int i = 2; i < tokens->argCount; i++) {
			tokenReduced->args[i - 2] = initString(tokens->args[i]->str);
		}
		tokenReduced->argCount = tokens->argCount - 2;
		for (int i = 0; i < repeats; i++) {
			TokenArray *tokenCopy = duplicateTokenArray(tokenReduced);
			executeCommand(tokenCopy);
		}
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
