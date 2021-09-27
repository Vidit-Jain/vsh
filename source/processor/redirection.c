#include "redirection.h"

int originalInput, originalOutput;

// Sets input to file described by inputFile
int setInputRedirect(String *inputFile) {
	int fd = open(inputFile->str, O_RDONLY);
	if (fd < 0) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	originalInput = dup(0);
	if (dup2(fd, 0) < 0) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	if (close(fd) < 0) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	return 0;
}

// Resets input to stdin
int resetInputRedirect() {
	if (dup2(originalInput, 0) < 0) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	return 0;
}

/* Sets output to file described by outputFile, overwrites or appends based
 * on the value of outputStyle, 0 - Overwrite, 1 - Append
 */
int setOutputRedirect(String *outputFile, int outputStyle) {
	int fd;
	if (outputStyle == 1)
		fd = open(outputFile->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(outputFile->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	originalOutput = dup(1);
	if (dup2(fd, 1) < 0) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	if (close(fd) < 0) {
		return -1;
	}
	return 0;
}

// Sets output to stdout again
int resetOutputRedirect() {
	if (dup2(originalOutput, 1) < 0) {
		errorHandler(GENERAL_NONFATAL);
		return -1;
	}
	return 0;
}