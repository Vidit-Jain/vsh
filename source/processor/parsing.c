#include "parsing.h"
// Used to remove the two tokens from the token array if redirection is used.
void shiftTwiceBack(TokenArray *tokens, int position) {
	for (int i = position + 2; i < tokens->argCount; i++) {
		if (tokens->args[i - 2] != NULL)
			free(tokens->args[i - 2]->str);
		free(tokens->args[i - 2]);
		tokens->args[i - 2] = initString(tokens->args[i]->str);
	}
	tokens->argCount -= 2;
}
/*
 * Parses the token input to check for file redirection. If redirection is
 * used, then inputFile and/or outputFile are filled.
 */
int parseRedirection(TokenArray *tokens, String **inputFile,
					 String **outputFile, int *outputStyle) {
	*outputStyle = 0;
	for (int i = 0; i < tokens->argCount; i++) {
		if (strcmp(tokens->args[i]->str, "<") == 0) {
			if (i == tokens->argCount - 1 || *inputFile != NULL) {
				return -1;
			}
			*inputFile = initString(tokens->args[i + 1]->str);
			shiftTwiceBack(tokens, i);
			i--;
		} else if (strcmp(tokens->args[i]->str, ">") == 0) {
			if (i == tokens->argCount - 1 || *outputFile != NULL) {
				return -1;
			}
			*outputFile = initString(tokens->args[i + 1]->str);
			*outputStyle = 1;
			shiftTwiceBack(tokens, i);
			i--;
		} else if (strcmp(tokens->args[i]->str, ">>") == 0) {
			if (i == tokens->argCount - 1 || *outputFile != NULL) {
				return -1;
			}
			*outputFile = initString(tokens->args[i + 1]->str);
			*outputStyle = 2;
			shiftTwiceBack(tokens, i);
			i--;
		}
	}
	return 0;
}