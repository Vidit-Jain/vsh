#include "exec.h"
#include "prompt.h"
void sigint_handler() { exit(0); }
int isBackgroundProcess(TokenArray *tokens) {
	String *lastToken = tokens->args[tokens->argCount - 1];
	return lastToken->str[lastToken->length - 1] == '&';
}

void exec(TokenArray *tokens) {
	pid_t childId = fork();
	if (childId == -1) {
		errorHandler(GENERAL_NONFATAL);
		return;
	}
	if (childId == 0) {
		signal(SIGINT, sigint_handler);
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
		pid_t grandChildId = fork();
		if (grandChildId == 0) {
			char *args[tokens->argCount + 1];
			for (int i = 0; i < tokens->argCount; i++) {
				args[i] = tokens->args[i]->str;
			}
			args[tokens->argCount] = NULL;
			execvp(tokens->args[0]->str, args);
			exit(0);
		} else {
			if (isBackground) {
				signal(SIGINT, SIG_IGN);
				printf("\n%d\n", grandChildId);
				printPrompt();
			}
			int status;
			wait(&status);
			char *message = WIFEXITED(status) ? "normally" : "abnormally";
			if (isBackground) {
				printf("\n%s with pid %d exited %s\n", tokens->args[0]->str,
					   grandChildId, message);
				printPrompt();
			}
			exit(0);
		}
	} else {
		if (!isBackgroundProcess(tokens)) {
			int status;
			wait(&status);
		}
	}
}