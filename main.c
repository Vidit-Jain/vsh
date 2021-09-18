#include "source/commands/history.h"
#include "source/processor/execute.h"
#include "source/processor/prompt.h"
#include "source/processor/signalHandling.h"
#include "source/utils/tokenArray.h"
#include "source/utils/utils.h"
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
