#include "repeat.h"

int commandRepeat(TokenArray *tokens) {
	if (tokens->argCount < 2) {
		printf("repeat: Incorrect number of arguments\n");
		return -1;
	}
	if (!isNumber(tokens->args[1])) {
		printf("repeat: Enter a number along with the command\n");
		return -1;
	}
	int repeats = (int)toNumber(tokens->args[1]);
	return repeats;
}