#include "cd.h"

void changeDirectory(TokenArray *tokens) {
	if (tokens->argCount == 1) { // Goto home
		stringCopy(previousPath, *currentPath);
		stringCopy(currentPath, *homePath);
		goToCurrentPath();
	} else if (isEqualString(*tokens->args[1],
							 *initString("-"))) { // Goto previous path
		String *temp = newString();
		stringCopy(temp, *currentPath);
		stringCopy(currentPath, *previousPath);
		stringCopy(previousPath, *temp);
		goToCurrentPath();
		printf("%s\n", currentPath->str);
	} else { // Attempt to change to directory specified
		if (chdir(tokens->args[1]->str) == -1) {
			errorHandler(GENERAL_NONFATAL);
			return;
		}
		stringCopy(previousPath, *currentPath);
		setCurrentPath();
	}
}

void commandCD(TokenArray *tokens) {
	// > 2 args aren't allowed (first arg being cd)
	if (tokens->argCount > 2) {
		errorHandler(INCORRECT_ARGC);
		return;
	}
	changeDirectory(tokens);
}