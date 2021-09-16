#include "cd.h"

void changeDirectory(TokenArray *tokens) {
	String *expandedPath = newString();
	expandPath(&expandedPath, tokens->args[1]);
	if (tokens->argCount == 1 ||
		isEqualString(*expandedPath, *initString("~"))) {
		stringCopy(previousPath, *currentPath);
		stringCopy(currentPath, *homePath);
		goToCurrentPath();
	} else if (isEqualString(*expandedPath, *initString("-"))) {
		String *temp = newString();
		stringCopy(temp, *currentPath);
		stringCopy(currentPath, *previousPath);
		stringCopy(previousPath, *temp);
		goToCurrentPath();
	} else {
		stringCopy(previousPath, *currentPath);
		if (chdir(expandedPath->str) == -1) {
			errorHandler(GENERAL_NONFATAL);
		}
		setCurrentPath();
	}
}

void commandCD(TokenArray *tokens) {
	if (tokens->argCount > 2) {
		errorHandler(INCORRECT_ARGC);
		return;
	}
	changeDirectory(tokens);
}