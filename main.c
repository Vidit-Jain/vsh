#include <ctype.h>
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
        resetHistoryIndex();
        setbuf(stdout, NULL);
        enableRawMode();
		printPrompt();
		input->length = 0;
		char inputCharacter;
        while (read(STDIN_FILENO, &inputCharacter, 1) == 1) {
            if (iscntrl(inputCharacter)) {
                if (inputCharacter == 10) {
                    printf("\n");
                    break;
                }
                if (inputCharacter == 27) {
                    char buffer[3];
                    buffer[2] = 0;
                    if (read(STDIN_FILENO, buffer, 2) == 2) {
                        if (buffer[1] == 'A'){
                            upArrow(input);
                        }
                        else if (buffer[1] == 'B') {
                            downArrow(input);
                        }
                    }
                } else if (inputCharacter == 127) {
                    if (input->length > 0) {
                        if (input->str[input->length - 1] == 9) {
                            for (int i = 0; i < 7; i++) printf("\b");
                        }
                        input->str[--input->length] = '\0';
                        printf("\b \b");
                    }
                } else if (inputCharacter == 9) {
                    input->str[input->length++] = inputCharacter;
                    for (int i = 0; i < 8; i++)
                        printf(" ");
                } else if (inputCharacter == 4) {
                    exit(0);
                } else {
                    printf("%c\n", inputCharacter);
                }
            }
            else {
                input->str[input->length++] = inputCharacter;
                printf("%c", inputCharacter);
            }
            }
            disableRawMode();
            input->str[input->length] = '\0';
            addHistory(input);
            executeLine(tokens, *input);
        }
}
