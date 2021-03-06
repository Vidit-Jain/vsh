#include "prompt.h"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RESET "\033[0m"
// Print the prompt username, systemname and current directory
void printPrompt() {
	if (displayPath != NULL)
		free(displayPath->str);
	free(displayPath);
	displayPath = shortenPath(currentPath);
	printf(GREEN "<%s@%s:" BLUE "%s" GREEN "> " RESET, username->str,
		   systemName->str, displayPath->str);
	fflush(stdout);
}