#include "source/commands/history.h"
#include "source/processor/execute.h"
#include "source/processor/prompt.h"
#include "source/processor/runningProcesses.h"
#include "source/utils/tokenArray.h"
#include "source/utils/utils.h"
void child_handler(int num) {
	int code;
	pid_t pid;
	while ((pid = waitpid(-1, &code, WNOHANG | WUNTRACED)) > 0) {
		char *name = processName(pid);
		if (name == NULL)
			continue;

		if (WIFEXITED(code)) {
			fprintf(stderr, "\n%s with pid %d exited normally\n", name, pid);
		} else if (WIFSTOPPED(code)) {
			fprintf(stderr, "\n%s with pid %d suspended normally\n", name, pid);
		} else {
			fprintf(stderr, "\n%s with pid %d exit abnormally\n", name, pid);
		}
		removeProcess(pid);
		printPrompt();
		fflush(stderr);
	}
}
int main() {
	signal(SIGINT, SIG_IGN);
	signal(SIGCHLD, child_handler);
	initInfo();
	String *input = newString();
	TokenArray *tokens = newTokenArray();
	while (1) {
		printPrompt();
		input->length = 0;
		char inputCharacter;
		while (1) {
			inputCharacter = (char)getchar();
			if (inputCharacter == '\n')
				break;

			input->str[input->length] = inputCharacter;
			input->length++;
		}
		input->str[input->length] = '\0';
		addHistory(input);
		executeLine(tokens, *input);
	}
}
