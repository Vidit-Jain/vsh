#include "prompt.h"

void printPrompt() {
	shortenPath(&displayPath, currentPath);
	printf("<%s@%s:%s> ", username->str, systemName->str, displayPath->str);
}