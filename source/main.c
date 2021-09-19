#include "commands/history.h"
#include "processor/execute.h"
#include "processor/prompt.h"
#include "processor/signalHandling.h"
#include "utils/tokenArray.h"
#include "utils/utils.h"
#include <ctype.h>
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
		// Read a character
		while (read(STDIN_FILENO, &inputCharacter, 1) == 1) {
			// If the character is a control character
			if (iscntrl(inputCharacter)) {
				// If newline, print a newline and stop taking input
				if (inputCharacter == 10) {
					printf("\n");
					break;
				}
				// 27 - indicates it could be an arrow key
				if (inputCharacter == 27) {
					char buffer[3];
					buffer[2] = 0;
					//
					if (read(STDIN_FILENO, buffer, 2) == 2) {
						// 'A' indicates it will be an up arrow key
						if (buffer[0] == '[' && buffer[1] == 'A') {
							upArrow(input);
						} else if (buffer[0] == '[' &&
								   buffer[1] == 'B') { // 'B' indicates it will
													   // be a down arrow key
							downArrow(input);
						}
					}
				} else if (inputCharacter == 127) { // 127 - Backspace key
					if (input->length > 0) {
						if (input->str[input->length - 1] ==
							9) { // Handle tabs separately
							for (int i = 0; i < 7; i++)
								printf("\b");
						}
						input->str[--input->length] = '\0';
						// Method for backspacing. Go one character behind,
						// overwrite with space and go back again
						printf("\b \b");
					}
				} else if (inputCharacter == 9) { // 9 == tab
					input->str[input->length++] = inputCharacter;
					for (int i = 0; i < 8; i++) // Print 8 spaces
						printf(" ");
				} else if (inputCharacter == 4) { // 4 == End of transmission
					exitShell();
				} else { // Unhandled control sequence, can just print, don't
						 // store in input
					printf("%c\n", inputCharacter);
				}
			} else {
				// Normal character, store in input
				input->str[input->length++] = inputCharacter;
				printf("%c", inputCharacter);
			}
		}
		disableRawMode();
		input->str[input->length] = '\0';
		if (input->length == 0)
			continue;
		addHistory(input);
		executeLine(tokens, *input);
	}
}
