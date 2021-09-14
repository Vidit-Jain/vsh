#include "pinfo.h"

int isForeground(pid_t pid) {
	pid_t pgid = getpgid(pid);
	return pgid == pid;
}

String *getExecutablePath(pid_t pid) {
	String *actualPath = newString();
	String *procPath = newString();
	sprintf(procPath->str, "/proc/%d/exe", pid);
	char *result = realpath(procPath->str, actualPath->str);
	return actualPath;
}

String *getState(pid_t pid) {
	String *fileName = newString();
	sprintf(fileName->str, "/proc/%d/stat", pid);
	FILE *fp = fopen(fileName->str, "rb");
	if (fp == NULL) {
		perror("Error: ");
		return NULL;
	}
	String *state = newString();
	char *buffer = (char *)malloc(100 * sizeof(char));
	for (int i = 0; i < 2; i++)
		fscanf(fp, "%s", buffer);
	fscanf(fp, "%s", state->str);
	return state;
}

unsigned long getVirtualMemorySize(pid_t pid) {
	String *fileName = newString();
	sprintf(fileName->str, "/proc/%d/stat", pid);
	FILE *fp = fopen(fileName->str, "rb");
	if (fp == NULL) {
		perror("Error: ");
		return -1;
	}
	String *state = newString();
	char *buffer = (char *)malloc(100 * sizeof(char));
	for (int i = 0; i < 22; i++)
		fscanf(fp, "%s", buffer);
	fscanf(fp, "%s", state->str);
	updateLength(state);
	unsigned long totalSize = toNumber(state);
	return totalSize / 1024;
}

void pinfo(pid_t pid) {
	printf("pid -- %d\n", pid);
	char *isPlus = isForeground(pid) ? "+" : "";
	printf("Process Status -- %s%s\n", getState(pid)->str, isPlus);

	unsigned long memorySize = getVirtualMemorySize(pid);
	printf("memory -- %lu\n", memorySize);

	String *executablePath = getExecutablePath(pid);
	printf("Executable Path -- %s\n", executablePath->str);
}

void commandPinfo(TokenArray *tokens) {
	pid_t pid = getpid();
	if (tokens->argCount != 1) {
		if (!isNumber(tokens->args[1])) {
			printf("pinfo: Invalid argument\n");
			return;
		}
		pid = (int)toNumber(tokens->args[1]);
	}
	pinfo(pid);
}
