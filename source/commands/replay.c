#include "replay.h"
TokenArray *commandReplay(TokenArray* tokens, int *interval, int *period, int *error) {

	TokenArray *repeatCommand = newTokenArray();
	int isCommandArgs = 0;
	for (int i = 1; i < tokens->argCount; i++) {
		if (tokens->args[i]->str[0] == '-') {
			if (strcmp(tokens->args[i]->str, "-command") == 0) {
				// Indicates "-command" was used twice in one call
				if (isCommandArgs) {
					*error = 1;
					break;
				}
				// Indicate the next tokens are the command tokens
				isCommandArgs = 1;
			}
			if (strcmp(tokens->args[i]->str, "-interval") == 0) {
				// Indicates end of command
				if (isCommandArgs) isCommandArgs = 0;
				// interval != -1 indicates interval was called before
				if (i == tokens->argCount - 1 || *interval != -1) {
					*error = 1;
					break;
				}
				if (!isNumber(tokens->args[i + 1])) {
					*error = 1;
					break;
				}
				*interval = (int)toNumber(tokens->args[i + 1]);
				i++;
			}
			if (strcmp(tokens->args[i]->str, "-period") == 0) {
				// Indicates end of command
				if (isCommandArgs) isCommandArgs = 0;
				// period != -1 indicates period was called before
				if (i == tokens->argCount - 1 || *period != -1) {
					*error = 1;
					break;
				}
				if (!isNumber(tokens->args[i + 1])) {
					*error = 1;
					break;
				}
				*period = (int)toNumber(tokens->args[i + 1]);
				i++;
			}

		}
		else if (isCommandArgs){
			// Add token to tokens of command
			repeatCommand->args[repeatCommand->argCount] = initString(tokens->args[i]->str);
			repeatCommand->argCount++;
		}
		else {
			// Extra argument, throw an error
			*error = 1;
			break;
		}

	}
	if (repeatCommand->argCount == 0) {
		*error = 1;
	}
	return repeatCommand;
}
