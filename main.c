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
		tokenize(tokens, *input);
		//        for (int i = 0; i < tokens->argCount; i++) {
		//            printf("\"%s\" ", tokens->args[i]->str);
		//        }
		//        printf("\n");
		execute(tokens);
	}
}