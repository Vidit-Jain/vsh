#include "prompt.h"

void printPrompt() {
	displayPath = shortenPath(currentPath);
	printf("<%s@%s:%s> ", username->str, systemName->str, displayPath->str);
	fflush(stdout);
}