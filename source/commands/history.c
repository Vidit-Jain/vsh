#include "history.h"
char *history[MAX_HISTORY];
int totalHistory;
int currentHistoryIndex = -1;

void createFile(char *name) {
	FILE *fp = fopen(name, "r");
	if (fp == NULL) {
		fp = fopen(name, "w");
		if (fp == NULL) {
			errorHandler(GENERAL_NONFATAL);
			return;
		}
		return;
	}
	if (fclose(fp) == EOF) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
}
void initHistory() {
	totalHistory = 0;
	String *historyPath = newString();
	sprintf(historyPath->str, "%s/.vsh_history", actualHome->str);
	createFile(historyPath->str);
	FILE *fp = fopen(historyPath->str, "r");
	if (fp == NULL) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	for (int i = 0; i < MAX_HISTORY; i++) {
		history[i] = (char *)malloc(MAX_COMMAND_SIZE * sizeof(char));
		if (history[i] == NULL)
			errorHandler(BAD_MALLOC);
	}

	while (fgets(history[totalHistory], MAX_COMMAND_SIZE, fp)) {
		int x = (int)strlen(history[totalHistory]);
		if (history[totalHistory][x - 1] == '\n')
			history[totalHistory][x - 1] = '\0';

		totalHistory++;
		if (totalHistory == MAX_HISTORY)
			break;
	}
}
void addHistory(String *command) {
	String *historyPath = newString();
	// Using $HOME for common vsh_history for all shell calls
	sprintf(historyPath->str, "%s/.vsh_history", actualHome->str);
	if (totalHistory != 0 && strcmp(command->str, history[0]) == 0)
		return;
	for (int i = MAX_HISTORY - 1; i > 0; i--) {
		history[i] = history[i - 1];
	}
	history[0] = (char *)malloc(MAX_COMMAND_SIZE * sizeof(char));
	if (history[0] == NULL)
		errorHandler(BAD_MALLOC);
	strcpy(history[0], command->str);
	totalHistory = MIN(totalHistory + 1, MAX_HISTORY);

	FILE *fp = fopen(historyPath->str, "w");
	if (fp == NULL) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	for (int i = 0; i < totalHistory; i++) {
		fprintf(fp, "%s", history[i]);
		if (i != totalHistory - 1) {
			fprintf(fp, "\n");
		}
	}
	if (fclose(fp) == EOF) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
}
void printHistory(int num) {
	num = MIN(num, totalHistory);
	for (int i = num - 1; i >= 0; i--) {
		printf("%s\n", history[i]);
	}
}
void resetHistoryIndex() { currentHistoryIndex = -1; }
void upArrow(String *input) {
	if (currentHistoryIndex + 1 >= totalHistory)
		return;
	eraseInput(input);
	currentHistoryIndex++;
	stringCopy(input, *initString(history[currentHistoryIndex]));
	printf("%s", input->str);
}
void downArrow(String *input) {
	if (currentHistoryIndex < 0)
		return;
	eraseInput(input);
	currentHistoryIndex--;
	if (currentHistoryIndex == -1)
		return;
	stringCopy(input, *initString(history[currentHistoryIndex]));
	printf("%s", input->str);
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