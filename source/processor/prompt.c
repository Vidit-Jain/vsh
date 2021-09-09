#include "prompt.h"

void printPrompt() {
	printf("<%s@%s:~> ", getUsername()->str, getSystemName()->str);
}