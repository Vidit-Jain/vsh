#include "utils.h"

struct termios default_teminal;
// Initializes variables at startup
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
// Erase input when up arrow or down arrow key is pressed
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
// Checks if string is a number
int isNumber(String *number) {
	for (int i = 0; i < number->length; i++) {
		if (number->str[i] < '0' || number->str[i] > '9')
			return 0;
	}
	return 1;
}
// Converts a string to a number
unsigned long toNumber(String *number) {
	unsigned long total = 0;
	for (int i = (int)0; i < (int)number->length; i++) {
		total *= 10;
		total += number->str[i] - '0';
	}
	return total;
}
// Given a path, it checks if such a folder exists
int folderExists(String path) {
	struct stat sb;
	return stat(path.str, &sb) == 0 && S_ISDIR(sb.st_mode);
}

// Given a path, it checks if such a file exists
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

// Disable rawmode to gain more control over the terminal
void disableRawMode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &default_teminal) == -1)
        errorHandler(GENERAL_FATAL);
}
// Enables rawmode to gain more control over the terminal
void enableRawMode() {
	if (tcgetattr(STDIN_FILENO, &default_teminal) == -1)
        errorHandler(GENERAL_FATAL);
    atexit(disableRawMode);
	struct termios rawInput = default_teminal;
	rawInput.c_lflag &= ~(ICANON | ECHO);

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawInput) == -1)
        errorHandler(GENERAL_FATAL);
}
