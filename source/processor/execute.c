#include "execute.h"

unsigned int isCommand(TokenArray *tokens, String str) {
	return isEqualString(*tokens->args[0], str);
}
void execute(TokenArray *tokens) {
	if (tokens->argCount == 0)
		return;
	if (isCommand(tokens, *initString("cd"))) {
		commandCd(tokens);
	}
	if (isCommand(tokens, *initString("echo"))) {
		commandEcho(tokens);
	}
}