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
		exitShell();
		break;
	case INVALID_SIZE:
		printError("Fatal Error: Invalid malloc size, aborting\n");
		exitShell();
		break;
	case GENERAL_FATAL:
		printPError("");
		exitShell();
		break;
	case GENERAL_NONFATAL: printPError(""); break;
	case INVALID_ARGCOUNT: printError("Incorrect number of arguments\n"); break;
	case INVALID_ARGS: printError("Invalid arguments passed\n"); break;
	default:
		printError("Unknown error, aborting");
		exitShell();
		break;
	}
}