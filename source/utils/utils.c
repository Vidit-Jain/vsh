#include "utils.h"

struct termios orig_termios;

void initInfo() {
	setHomePath();
	setCurrentPath();
	setActualHome();
	setUsername();
	setSystemName();
	previousPath = newString();
	stringCopy(previousPath, *currentPath);
	initProcessList();
	initHistory();
}

void eraseInput(String *input) {
	while (input->length != 0) {
		if (input->str[input->length - 1] == 9) {
			for (int i = 0; i < 7; i++)
				printf("\b");
		}
		printf("\b \b");
		input->length--;
	}
	input->str[0] = '\0';
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

int fileExists(String path) {
	struct stat sb;
	return stat(path.str, &sb) == 0 && S_ISREG(sb.st_mode);
}

String *getUser(uid_t uid) {
	struct passwd *user;
	user = getpwuid(uid);
	if (user == NULL)
		errorHandler(GENERAL_FATAL);
	return initString(user->pw_name);
}

String *getGroup(gid_t gid) {
	struct group *user;
	user = getgrgid(gid);
	if (user == NULL)
		errorHandler(GENERAL_FATAL);
	return initString(user->gr_name);
}

void die(const char *s) {
	perror(s);
	exit(1);
}

void disableRawMode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
		die("tcsetattr");
}

void enableRawMode() {
	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
		die("tcgetattr");
	atexit(disableRawMode);
	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcsetattr");
}
