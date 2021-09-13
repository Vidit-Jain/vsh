#include "exec.h"
#include <sys/wait.h>
#include <unistd.h>
int isBackgroundProcess(TokenArray *tokens) {
	String *lastToken = tokens->args[tokens->argCount - 1];
	return lastToken->str[lastToken->length - 1] == '&';
}

void exec(TokenArray *tokens) {
	pid_t childId = fork();
	if (childId == 0) {
		if (isBackgroundProcess(tokens)) {
			String *lastToken = tokens->args[tokens->argCount - 1];
			if (lastToken->length > 1) {
				lastToken->str[lastToken->length - 1] = '\0';
				lastToken->length--;
			} else {
				tokens->args[tokens->argCount - 1] = NULL;
				tokens->argCount--;
			}
		}
		char *args[tokens->argCount];
		for (int i = 0; i < tokens->argCount; i++) {
			args[i] = tokens->args[i]->str;
		}
		execvp(tokens->args[0]->str, args);
	} else {
        if (!isBackgroundProcess(tokens)) {
            int status;
            wait(&status);
        }
        else {
            printf("%d\n", childId);
        }
	}
}