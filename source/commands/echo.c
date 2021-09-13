#include "echo.h"

void commandEcho(TokenArray *tokens) {
	for (int i = 1; i < tokens->argCount; i++) {
		printf("%s%c", tokens->args[i]->str, " \n"[i == tokens->argCount - 1]);
	}
}