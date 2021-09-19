#include "execute.h"

unsigned int isCommand(TokenArray *tokens, String str) {
	return isEqualString(*tokens->args[0], str);
}
// Checks the first command and executes the appropriate command
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
	} else if (isCommand(tokens, *initString("history"))) {
		commandHistory(tokens);
	} else if (isCommand(tokens, *initString("exit"))) {
		exitShell();
	} else if (isCommand(tokens, *initString("repeat"))) {
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
		}
	} else {
		exec(tokens);
	}
}
// Tokenize the input by the ; to execute multiple commands.
void executeLine(TokenArray *tokens, String input) {
	char *currentCommand;
	String *parseInput = initString(input.str);
	while (
		(currentCommand = strtok_r(parseInput->str, ";", &parseInput->str))) {
		tokenizeCommand(tokens, *initString(currentCommand));
		executeCommand(tokens);
	}
}
