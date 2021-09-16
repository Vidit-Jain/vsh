#include "errorHandling.h"

void printError(const char *errorMessage) {
	printf("\033[0;31m");
	printf("%s\n", errorMessage);
	printf("\033[0m");
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
		perror("Error: ");
		exit(1);
		break;
	}
}