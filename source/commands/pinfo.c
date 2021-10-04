#include "pinfo.h"
// Returns whether process is in foreground or background
int isForeground(pid_t pid) {
	pid_t pgid = getpgid(pid);
	if (getpgid(pid) == -1)
		return -1;
	return pgid == pid;
}
// Checks /proc/<pid>/exe to find the executable path of the process
String *getExecutablePath(pid_t pid) {
	String *actualPath = newString();
	String *procPath = newString();
	sprintf(procPath->str, "/proc/%d/exe", pid);
	char *result = realpath(procPath->str, actualPath->str);
	if (result == NULL) {
		errorHandler(GENERAL_NONFATAL);
		return NULL;
	}
	updateLength(actualPath);
	return actualPath;
}
// Finds virtual memory used through /proc/<pid>/stat
unsigned long getVirtualMemorySize(pid_t pid) {
	String *fileName = newString();
	sprintf(fileName->str, "/proc/%d/stat", pid);
	FILE *fp = fopen(fileName->str, "rb");
	if (fp == NULL) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	String *state = newString();
	String *buffer = newString();
	for (int i = 0; i < 22; i++)
		fscanf(fp, "%s", buffer->str);
	fscanf(fp, "%s", state->str);
	updateLength(state);
	unsigned long totalSize = toNumber(state);
	return totalSize / 1024;
}
// Prints pinfo of a process specified
void pinfo(pid_t pid) {
	printf("pid -- %d\n", pid);
	if (isForeground(pid) == -1) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	char *isPlus = isForeground(pid) ? "+" : "";
	String *state = getState(pid);
	if (state == NULL)
		return;
	printf("Process Status -- %s%s\n", state->str, isPlus);

	unsigned long memorySize = getVirtualMemorySize(pid);
	if (memorySize == -1)
		return;
	printf("memory -- %lu kb\n", memorySize);

	String *executablePath = getExecutablePath(pid);
	if (executablePath == NULL)
		return;
	String *shortenedPath = shortenPath(executablePath);
	printf("Executable Path -- %s\n", shortenedPath->str);
}

void commandPinfo(TokenArray *tokens) {
	pid_t pid = getpid(); // Default if no argument is passed

	if (tokens->argCount > 2) {
		errorHandler(INCORRECT_ARGC);
		return;
	}

	if (tokens->argCount != 1) {
		if (!isNumber(tokens->args[1])) {
			errorHandler(INVALID_ARGS);
			return;
		}
		pid = (int)toNumber(tokens->args[1]);
	}
	pinfo(pid);
}
