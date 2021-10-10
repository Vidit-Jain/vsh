#include "execute.h"

unsigned int isCommand(TokenArray *tokens, char *str) {
	return strcmp(tokens->args[0]->str, str) == 0;
}
// Checks the first command and executes the appropriate command
void executeCommand(TokenArray *tokens) {
	if (tokens->argCount == 0)
		return;
	else if (isCommand(tokens, "cd")) {
		commandCD(tokens);
	} else if (isCommand(tokens, "echo")) {
		commandEcho(tokens);
	} else if (isCommand(tokens, "pwd")) {
		commandPWD(tokens);
	} else if (isCommand(tokens, "ls")) {
		commandLS(tokens);
	} else if (isCommand(tokens, "pinfo")) {
		commandPinfo(tokens);
	} else if (isCommand(tokens, "history")) {
		commandHistory(tokens);
	} else if (isCommand(tokens, "jobs")) {
		commandJobs(tokens);
	} else if (isCommand(tokens, "sig")) {
		commandSig(tokens);
	} else if (isCommand(tokens, "bg")) {
		commandBg(tokens);
	} else if (isCommand(tokens, "fg")) {
		commandFg(tokens);
	} else if (isCommand(tokens, "baywatch")) {
		commandBaywatch(tokens);
	} else if (isCommand(tokens, "exit")) {
		exitShell();
	} else if (isCommand(tokens, "repeat")) {
		/* If repeat is called, the first two commands are removed
		 * and the rest of the command is executed multiple times in a loop
		 */

		int repeats = commandRepeat(tokens);
		if (repeats == -1) {
			return;
		}
		TokenArray *tokenReduced = newTokenArray();
		for (int i = 2; i < tokens->argCount; i++) {
			tokenReduced->args[i - 2] = initString(tokens->args[i]->str);
		}
		tokenReduced->argCount = tokens->argCount - 2;
		for (int i = 0; i < repeats; i++) {
			TokenArray *tokenCopy = duplicateTokenArray(tokenReduced);
			executeCommand(tokenCopy);
			free(tokenCopy);
		}
	} else if (isCommand(tokens, "replay")) {
		int error = 0, period = -1, interval = -1;
		TokenArray *repeatCommand =
			commandReplay(tokens, &interval, &period, &error);
		if (error) {
			fprintf(stderr, "\033[0;31m");
			fprintf(stderr, "Invalid usage of repeat command\n");
			fprintf(stderr, "\033[0m");
			return;
		}
		time_t start = time(NULL);
		while (1) {
			time_t curr = time(NULL);
			// If not enough time to execute once more, just sleep for time left
			if (period - curr + start < interval) {
				sleep(period - curr + start);
				break;
			}
			// Sleep for interval specified
			sleep(interval);
			// Take a copy of the command to be executed
			TokenArray *tokenPass = duplicateTokenArray(repeatCommand);
			executeCommand(tokenPass);
		}
	} else {
		exec(tokens);
	}
}

// Tokenize the input by the ; to execute multiple commands.
void executeLine(TokenArray *tokens, String input) {
	char *currentCommand;
	String *parseInput = initString(input.str);
	char *tempStore = parseInput->str;
	while (
		(currentCommand = strtok_r(parseInput->str, ";", &parseInput->str))) {

		char *subCommands[20];
		int commandCount = 0;
		while ((subCommands[commandCount] =
					strtok_r(currentCommand, "|", &currentCommand)))
			commandCount++;

		int oldpipefds[2];
		int pipefds[2];
		int originalInput = dup(0);
		int originalOutput = dup(1);
		for (int i = 0; i < commandCount; i++) {
			if (pipe(pipefds) == -1) {
				errorHandler(GENERAL_NONFATAL);
				return;
			}
			if (i != 0) {
				// Take input from previous pipe
				dup2(oldpipefds[0], 0);
				if (close(oldpipefds[0]) < 0) {
					errorHandler(GENERAL_NONFATAL);
					return;
				}
			}
			if (i != commandCount - 1) {
				// Give output to current pipe
				dup2(pipefds[1], 1);
				if(close(pipefds[1]) < 0) {
					errorHandler(GENERAL_NONFATAL);
					return;
				}
			}
			tokenizeCommand(tokens, subCommands[i]);
			String *inputFile = NULL, *outputFile = NULL;
			int outputStyle = 0;
			if (parseRedirection(tokens, &inputFile, &outputFile,
								 &outputStyle) < 0) {
				fprintf(stderr, "\033[0;31m");
				fprintf(stderr, "Error while parsing command\n");
				fprintf(stderr, "\033[0m");
				return;
			}
			if (outputFile != NULL) {
				if (setOutputRedirect(outputFile, outputStyle) < 0) {
					return;
				}
			}
			if (inputFile != NULL) {
				if (setInputRedirect(inputFile) < 0) {
					return;
				}
			}
			executeCommand(tokens);

			// Switch new pipe to old pipe
			oldpipefds[0] = pipefds[0];
			oldpipefds[1] = pipefds[1];

			// Switch to stdin, stdout
			dup2(originalInput, 0);
			dup2(originalOutput, 1);
		}

		// Close lone fd that is unclosed
		close(oldpipefds[0]);
	}
	free(tempStore);
	free(parseInput);
}
