#include "echo.h"
// Prints all the tokens supplied to the command
void commandEcho(TokenArray *tokens) {
	for (int i = 1; i < tokens->argCount; i++) {
		printf("%s%c", tokens->args[i]->str, " \n"[i == tokens->argCount - 1]);
	}
}