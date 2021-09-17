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

unsigned int inHomeDirectory(String *path) {
	if (homePath->length > path->length)
		return 0;

	for (int i = 0; i < homePath->length; i++)
		if (homePath->str[i] != path->str[i])
			return 0;

	return 1;
}

String *shortenPath(String *path) {
	String *shortenedPath = newStringCustom(PATH_MAX);
	if (!inHomeDirectory(path)) {
		stringCopy(shortenedPath, *path);
		return shortenedPath;
	}
	sprintf(shortenedPath->str, "~%s", &(path->str[homePath->length]));
	updateLength(shortenedPath);
	return shortenedPath;
}
String *expandPath(String *path) {
	String *expandedPath = newStringCustom(PATH_MAX);
	if (path->str[0] != '~') {
		stringCopy(expandedPath, *path);
		return expandedPath;
	}
	stringCopy(expandedPath, *homePath);
	String *trimmedPath = initString(&path->str[1]);
	concatenate(expandedPath, trimmedPath);
}

void goToCurrentPath() {
	if (chdir(currentPath->str) == -1) {
		errorHandler(GENERAL_NONFATAL);
	}
	currentPathDepth = getDepth(*currentPath);
}