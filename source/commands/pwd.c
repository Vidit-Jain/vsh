#include "pwd.h"
void commandPWD(TokenArray *tokens) {
	if (tokens->argCount != 1) {
		printf("pwd: Too many arguments\n");
		return;
	}
	printf("%s\n", currentPath->str);
}