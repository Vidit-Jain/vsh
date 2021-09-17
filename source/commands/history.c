#include "history.h"
void createFile(char *name) {
	FILE *fp = fopen(name, "wb");
	if (fp == NULL) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	if (fclose(fp) == EOF) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
}
void addHistory(String *command) {
	String *historyPath = newString();
	sprintf(historyPath->str, "%s/.vsh_history", actualHome->str);
	// Using $HOME for common vsh_history for all shell calls
	FILE *fp = fopen(historyPath->str, "r");
	if (fp == NULL) {
		createFile(historyPath->str);
		fp = fopen(historyPath->str, "r");
		if (fp == NULL) {
			errorHandler(GENERAL_NONFATAL);
			return;
		}
	}
	char *history[20];
	for (int i = 0; i < 20; i++)
		history[i] = (char *)malloc(MAX_COMMAND_SIZE * sizeof(char));
	history[0] = command->str;
	int index = 1;
	while (fgets(history[index], MAX_COMMAND_SIZE, fp)) {
		int x = (int)strlen(history[index]);
		if (history[index][x - 1] == '\n')
			history[index][x - 1] = '\0';

		index++;
		if (index == 20)
			break;
	}
	if (fclose(fp) == EOF) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	fp = fopen(historyPath->str, "w");
	if (fp == NULL) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	for (int i = 0; i < index; i++) {
		fprintf(fp, "%s", history[i]);
		if (i != index - 1) {
			fprintf(fp, "\n");
		}
	}
	if (fclose(fp) == EOF) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
}
void printHistory(int num) {
	String *historyPath = newString();
	sprintf(historyPath->str, "%s/.vsh_history", actualHome->str);
	FILE *fp = fopen(historyPath->str, "r");
	if (fp == NULL) {
		return;
	}
	char *history[20];
	for (int i = 0; i < 20; i++)
		history[i] = (char *)malloc(MAX_COMMAND_SIZE * sizeof(char));
	int index = 0;
	while (fgets(history[index], MAX_COMMAND_SIZE, fp)) {
		int x = (int)strlen(history[index]);
		if (history[index][x - 1] == '\n')
			history[index][x - 1] = '\0';

		index++;
		if (index == num)
			break;
	}
	for (int i = index - 1; i >= 0; i--) {
		printf("%s\n", history[i]);
	}
	if (fclose(fp) == EOF) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
}
void commandHistory(TokenArray *tokens) {
	if (tokens->argCount > 2) {
		errorHandler(INCORRECT_ARGC);
		return;
	}
	if (tokens->argCount == 2) {
		if (!isNumber(tokens->args[1])) {
			errorHandler(INVALID_ARGS);
			return;
		}
		int num = (int)toNumber(tokens->args[1]);
		if (num == 0)
			return;
		printHistory(num);
	} else
		printHistory(10);
}