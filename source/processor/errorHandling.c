#include "errorHandling.h"

void printError(const char *errorMessage) {
	fprintf(stderr, "\033[0;31m");
	fprintf(stderr, "%s", errorMessage);
	fprintf(stderr, "\033[0m");
}
void printPError(const char *errorMessage) {
	fprintf(stderr, "\033[0;31m");
	perror(errorMessage);
	fprintf(stderr, "\033[0m");
}
void errorHandler(int code) {
	switch (code) {
	case BAD_MALLOC:
		printError("Fatal Error: Bad malloc, aborting\n");
		exit(1);
		break;
	case INVALID_SIZE:
		printError("Fatal Error: Invalid malloc size, aborting\n");
		exit(1);
		break;
	case GENERAL_FATAL:
		printPError("");
		exit(1);
		break;
	case GENERAL_NONFATAL: printPError(""); break;
	case INCORRECT_ARGC: printError("Incorrect number of arguments\n"); break;
	case INVALID_ARGS: printError("Invalid arguments passed\n"); break;
	default: printError("Unknown error, aborting"); break;
	}
}