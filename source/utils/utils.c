#include "utils.h"

void initInfo() {
	setHomePath();
	setCurrentPath();
	previousPath = newString();
	setUsername();
	setSystemName();
	stringCopy(previousPath, *currentPath);
}

int isNumber(TokenArray *tokens) {
	String *repeats = tokens->args[1];
	for (int i = 0; i < repeats->length; i++) {
		if (repeats->str[i] < '0' || repeats->str[i] > '9')
			return 0;
	}
	return 1;
}

int toNumber(TokenArray *tokens) {
	String *repeats = tokens->args[1];
	int number = 0;
	for (int i = (int)repeats->length - 1; i >= 0; i--) {
		number *= 10;
		number += repeats->str[i] - '0';
	}
	return number;
}

int folderExists(String path) {
	struct stat sb;
	return stat(path.str, &sb) == 0 && S_ISDIR(sb.st_mode);
}

String *getUser(uid_t uid) {
	struct passwd *user;
	user = getpwuid(uid);
	return initString(user->pw_name);
}

String *getGroup(gid_t gid) {
	struct group *user;
	user = getgrgid(gid);
	return initString(user->gr_name);
}
