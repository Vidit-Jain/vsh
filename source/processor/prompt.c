#include "prompt.h"
void initInfo() {
	setHomePath();
	getCurrentPath();
	previousPath = newString();
	stringCopy(previousPath, *currentPath);
}
void printPrompt() {
	updateDisplayPath();
	printf("<%s@%s:%s> ", getUsername()->str, getSystemName()->str,
		   displayPath->str);
}