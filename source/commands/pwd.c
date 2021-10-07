#include "pwd.h"

// Prints the user's current working directory
void commandPWD(TokenArray *tokens) {
	if (tokens->argCount != 1) {
		errorHandler(INVALID_ARGCOUNT);
		return;
	}
	printf("%s\n", currentPath->str);
}