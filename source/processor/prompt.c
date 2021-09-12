#include "prompt.h"
void initInfo() {
	setHomePath();
    setCurrentPath();
	previousPath = newString();
    setUsername();
    setSystemName();
	stringCopy(previousPath, *currentPath);
}
void printPrompt() {
	updateDisplayPath();
	printf("<%s@%s:%s> ", username->str, systemName->str,
           displayPath->str);
}