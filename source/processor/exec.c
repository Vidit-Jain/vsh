#include "exec.h"
int isBackgroundProcess(TokenArray *tokens) {
	String *lastToken = tokens->args[tokens->argCount - 1];
	return lastToken->str[lastToken->length - 1] == '&';
}

void exec(TokenArray *tokens) {
	int isBackground = isBackgroundProcess(tokens);
	if (isBackground) {
		String *lastToken = tokens->args[tokens->argCount - 1];
		if (lastToken->length > 1) {
			lastToken->str[lastToken->length - 1] = '\0';
			lastToken->length--;
		} else {
			tokens->args[tokens->argCount - 1] = NULL;
			tokens->argCount--;
		}
	}
	pid_t childId = fork();
	if (childId == -1) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	if (childId == 0) {
		signal(SIGINT, sigint_handler);
		char *args[tokens->argCount + 1];
		for (int i = 0; i < tokens->argCount; i++) {
			args[i] = tokens->args[i]->str;
		}
		args[tokens->argCount] = NULL;
		execvp(tokens->args[0]->str, args);
		errorHandler(GENERAL_NONFATAL);
		exit(0);
	} else {
		if (!isBackground) {
			int status;
			wait(&status);
		} else {
			printf("%d\n", childId);
			addProcess(tokens->args[0]->str, childId);
		}
	}
}