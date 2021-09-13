#include "prompt.h"

void printPrompt() {
	updateDisplayPath();
	printf("<%s@%s:%s> ", username->str, systemName->str, displayPath->str);
}