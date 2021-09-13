#include "repeat.h"

int commandRepeat(TokenArray *tokens) {
	if (tokens->argCount < 2) {
		printf("repeat: Incorrect number of arguments\n");
		return -1;
	}
	if (!isNumber(tokens)) {
		printf("repeat: Enter a number along with the command\n");
		return -1;
	}
	int repeats = toNumber(tokens);
	return repeats;
}