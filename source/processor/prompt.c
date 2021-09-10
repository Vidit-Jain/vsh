#include "prompt.h"

void printPrompt() {
    updateDisplayPath();
	printf("<%s@%s:%s> ", getUsername()->str, getSystemName()->str, displayPath->str);
}