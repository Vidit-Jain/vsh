#include "utils.h"

void initInfo() {
	setHomePath();
	setCurrentPath();
	previousPath = newString();
	setUsername();
	setSystemName();
	stringCopy(previousPath, *currentPath);
}

int isNumber(String *number) {
	for (int i = 0; i < number->length; i++) {
		if (number->str[i] < '0' || number->str[i] > '9')
			return 0;
	}
	return 1;
}

unsigned long toNumber(String *number) {
	unsigned long total = 0;
	for (int i = (int)0; i < (int)number->length; i++) {
        total *= 10;
        total += number->str[i] - '0';
	}
	return total;
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