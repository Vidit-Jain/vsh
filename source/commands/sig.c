#include "sig.h"
// Given the job number and signal number, send the signal to the process.
void sendSignal(int jobNumber, int signalNumber) {
	int totalProcesses = getTotalProcesses();
	char *processNames[totalProcesses];
	pid_t ids[totalProcesses];

	currentProcesses(processNames, ids);

	// Specified process doesn't exist if > total processes.
	if (jobNumber > totalProcesses) {
		fprintf(stderr, "\033[0;31m");
		fprintf(stderr, "Job [%d] doesn't exist\n", jobNumber);
		fprintf(stderr, "\033[0m");
		return;
	}

	pid_t process = ids[jobNumber - 1];
	// If the kill operation fails, output the error thrown
	if (kill(process, signalNumber) != 0) {
		errorHandler(GENERAL_NONFATAL);
	}
}
void commandSig(TokenArray *tokens) {
	// Command must have exactly 3 arguments
	if (tokens->argCount != 3) {
		errorHandler(INCORRECT_ARGC);
		return;
	}
	// Check if both of the arguments are numbers
	if (!isNumber(tokens->args[1]) || !isNumber(tokens->args[2])) {
		errorHandler(INVALID_ARGS);
		return;
	}
	// Extract the job and signal number specified
	int jobNumber = (int)toNumber(tokens->args[1]);
	int signalNumber = (int)toNumber(tokens->args[1]);
	sendSignal(jobNumber, signalNumber);
}