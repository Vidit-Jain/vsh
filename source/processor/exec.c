#include "exec.h"
// Checks tokens to see if process is to be run in background
int isBackgroundProcess(TokenArray *tokens) {
	String *lastToken = tokens->args[tokens->argCount - 1];
	return lastToken->str[lastToken->length - 1] == '&';
}
// Executes set of tokens received using execvp and fork
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
		// Child process should terminate on SIGINT
		signal(SIGINT, sigint_handler);
		char *args[tokens->argCount + 1];
		for (int i = 0; i < tokens->argCount; i++) {
			args[i] = tokens->args[i]->str;
		}
		setpgid(0, 0);
		args[tokens->argCount] = NULL;
		execvp(tokens->args[0]->str, args);
		errorHandler(GENERAL_NONFATAL);
		exit(0);
	} else {
		if (!isBackground) { // Wait if not background process
			signal(SIGTTOU, SIG_IGN);
			signal(SIGTTIN, SIG_IGN);
			tcsetpgrp(STDIN_FILENO, childId);

			int status;
			wait(&status);
			waitpid(childId, &status, WUNTRACED);

			tcsetpgrp(STDIN_FILENO, getpgrp());
			signal(SIGTTOU, SIG_DFL);
			signal(SIGTTIN, SIG_DFL);
		} else {
			printf("%d\n", childId);
			// Add child process to linked list of currently running processes
			addProcess(tokens->args[0]->str, childId);
		}
	}
}