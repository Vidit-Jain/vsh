#include "repeat.h"
// Allows you to repeat a command multiple times
int commandRepeat(TokenArray *tokens) {
	if (tokens->argCount < 2) {
		errorHandler(INCORRECT_ARGC);
		return -1;
	}
	if (!isNumber(tokens->args[1])) {
		errorHandler(INVALID_ARGS);
		return -1;
	}
	int repeats = (int)toNumber(tokens->args[1]);
	return repeats;
}