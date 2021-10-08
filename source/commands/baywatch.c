#include "baywatch.h"
void newborn() {
	FILE *fp = fopen("/proc/loadavg", "rb");
	if (fp == NULL) {
		printf("Error\n");
	}
	String *state = newString();
	String *buffer = newString();
	// Fifth value is the latest pid
	for (int i = 0; i < 4; i++)
		fscanf(fp, "%s", buffer->str);
	fscanf(fp, "%s", state->str);
	updateLength(state);
	fclose(fp);
	printf("%s\n", state->str);
}
void dirty() {
	FILE *fp = fopen("/proc/meminfo", "rb");
	if (fp == NULL) {
		printf("Error\n");
		return;
	}
	String *state = newString();
	String *buffer = newString();
	// 49th token is the dirty memory value
	for (int i = 0; i < 16 * 3 + 1; i++)
		fscanf(fp, "%s", buffer->str);
	fscanf(fp, "%s", state->str);
	updateLength(state);
	fclose(fp);
	printf("%s kb\n", state->str);
}
int checkFlagsBaywatch(TokenArray *tokens, char **command) {
	char *args[tokens->argCount];
	for (int i = 0; i < tokens->argCount; i++) {
		args[i] = tokens->args[i]->str;
	}
	char *durationString;
	int duration = 0;
	int opt;
	while ((opt = getopt((int)tokens->argCount, args, ":n:")) != -1) {
		switch (opt) {
		case 'n': durationString = optarg; break;
		case ':':
			fprintf(stderr, "\033[0;31m");
			fprintf(stderr, "Argument not passed\n");
			fprintf(stderr, "\033[0m");
			duration = -1;
			break;
		case '?':
			errorHandler(INVALID_ARGS);
			duration = -1;
			break;
		default: errorHandler(INVALID_ARGS);
		}
		if (duration == -1)
			break;
	}
	if (duration == -1)
		return duration;
	if (durationString == NULL) {
		fprintf(stderr, "\033[0;31m");
		fprintf(stderr, "Duration not specified\n");
		fprintf(stderr, "\033[0m");
		return -1;
	}

	if (!isNumber(initString(durationString))) {
		errorHandler(INVALID_ARGS);
		return -1;
	}
	duration = (int)toNumber(initString(durationString));
	if (optind < tokens->argCount)
		*command = args[optind];
	else {
		errorHandler(INVALID_ARGS);
		return -1;
	}
	optind = 0;

	return duration;
}
void commandBaywatch(TokenArray *tokens) {
	if (tokens->argCount != 4) {
		errorHandler(INVALID_ARGCOUNT);
		return;
	}
	char *command = NULL;
	int command_id = -1;
	int duration = checkFlagsBaywatch(tokens, &command);

	if (duration == -1)
		return;
	if (strcmp(command, "interrupt") == 0) {
		command_id = 1;
	} else if (strcmp(command, "newborn") == 0) {
		command_id = 2;
	} else if (strcmp(command, "dirty") == 0) {
		command_id = 3;
	}
	if (command_id == -1) {
		errorHandler(INVALID_ARGS);
		return;
	}
	time_t prev = time(NULL);
	enableRawMode();
	setbuf(stdin, NULL);
	while (!keyPressed()) {
		time_t curr = time(NULL);
		// If sufficient time has past, then execute command
		if (curr - prev >= duration) {
			if (command_id == 2)
				newborn();
			else if (command_id == 3)
				dirty();
			prev = curr;
		}
	}
	disableRawMode();
}
