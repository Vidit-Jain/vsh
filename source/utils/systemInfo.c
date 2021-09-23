#include "systemInfo.h"
// Sets the global username variable to username of user
void setUsername() {
	struct passwd *pass = getpwuid(getuid());
	if (pass == NULL)
		errorHandler(GENERAL_FATAL);
	username = initString(pass->pw_name);
}

// Sets the global systemname variable to systemname of user
void setSystemName() {
	systemName = newString();
	if (gethostname(systemName->str, systemName->maxSize) == -1) {
		errorHandler(GENERAL_FATAL);
	}
	updateLength(systemName);
}
// Find actual home of user
void setActualHome() {
	if (actualHome != NULL)
		free(actualHome->str);
	free(actualHome);
	actualHome = newString();
	if ((actualHome->str = getenv("HOME")) == NULL) {
		actualHome->str = getpwuid(getuid())->pw_dir;
	}
}
// Find home path for this session of shell execution
String *setHomePath() {
	homePath = newStringCustom(PATH_MAX);
	if (getcwd(homePath->str, homePath->maxSize) != NULL) {
		updateLength(homePath);
		return homePath;
	} else {
		errorHandler(GENERAL_FATAL);
		return NULL;
	}
}
// Set the current to directory pointed by global currentPath variable
String *setCurrentPath() {
	currentPath = newStringCustom(PATH_MAX);
	if (getcwd(currentPath->str, currentPath->maxSize) != NULL) {
		updateLength(currentPath);
		return currentPath;
	} else {
		errorHandler(GENERAL_FATAL);
		return NULL;
	}
}
// Checks if path passed is inside home directory or not
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
	return expandedPath;
}

void goToCurrentPath() {
	if (chdir(currentPath->str) == -1) {
		errorHandler(GENERAL_NONFATAL);
	}
}