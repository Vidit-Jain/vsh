#include "source/processor/execute.h"
#include "source/processor/prompt.h"
#include "source/processor/tokenize.h"
#include "source/utils/tokenArray.h"
int main() {
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
        char* currentCommand;
        String *parseInput = initString(input->str);
        while ((currentCommand = strtok_r(parseInput->str, ";", &parseInput->str))) {
            tokenize(tokens, *initString(currentCommand));
            executeCommand(tokens);
        }
	}
}