#include "prompt.h"
void initInfo() {
    setHomePath();
    getCurrentPath();
}
void printPrompt() {
    updateDisplayPath();
	printf("<%s@%s:%s> ", getUsername()->str, getSystemName()->str, displayPath->str);
}