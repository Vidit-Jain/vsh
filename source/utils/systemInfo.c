#include "systemInfo.h"

void setUsername() {
	struct passwd *pass = getpwuid(getuid());
	if (pass == NULL)
		errorHandler(GENERAL_FATAL);
	username = initString(pass->pw_name);
}

void setSystemName() {
	systemName = newString();
	if (gethostname(systemName->str, systemName->maxSize) == -1) {
		errorHandler(GENERAL_FATAL);
	}
	updateLength(systemName);
}

unsigned int getDepth(String path) {
	unsigned depth = 0;
	for (int i = 0; i < path.length; i++) {
		if (path.str[i] == '/')
			depth++;
	}
	return depth;
}

String *setHomePath() {
	homePath = newStringCustom(PATH_MAX);
	if (getcwd(homePath->str, homePath->maxSize) != NULL) {
		updateLength(homePath);
		homePathDepth = getDepth(*homePath);
		return homePath;
	} else {
		errorHandler(GENERAL_FATAL);
		homePathDepth = 0;
		return NULL;
	}
}

String *setCurrentPath() {
	currentPath = newStringCustom(PATH_MAX);
	if (getcwd(currentPath->str, currentPath->maxSize) != NULL) {
		updateLength(currentPath);
		currentPathDepth = getDepth(*currentPath);
		return currentPath;
	} else {
		errorHandler(GENERAL_FATAL);
		currentPathDepth = 0;
		return NULL;
	}
}

unsigned int inHomeDirectory() {
	if (homePathDepth > currentPathDepth)
		return 0;
	if (homePath->length > currentPath->length)
		return 0;

	for (int i = 0; i < homePath->length; i++)
		if (homePath->str[i] != currentPath->str[i])
			return 0;

	return 1;
}

void updateDisplayPath() {
	if (displayPath == NULL)
		displayPath = newString(PATH_MAX);

	if (!inHomeDirectory()) {
		stringCopy(displayPath, *currentPath);
		return;
	}
	sprintf(displayPath->str, "~%s", &(currentPath->str[homePath->length]));
	updateLength(displayPath);
}

void goToCurrentPath() {
	if (chdir(currentPath->str) == -1) {
		errorHandler(GENERAL_NONFATAL);
	}
	currentPathDepth = getDepth(*currentPath);
}