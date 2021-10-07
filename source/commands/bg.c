#include "bg.h"

void commandBg(TokenArray* tokens) {
	if (tokens->argCount != 2) {
		errorHandler(INVALID_ARGCOUNT);
		return;
	}
	if (!isNumber(tokens->args[1])) {
		errorHandler(INVALID_ARGS);
		return;
	}
	int job_no = (int)toNumber(tokens->args[1]);
	pid_t pid = getJob(job_no);
	if (pid == -1) {
		fprintf(stderr, "\033[0;31m");
		fprintf(stderr, "Invalid job number\n");
		fprintf(stderr, "\033[0m");
		return;
	}
	if (kill(pid, SIGCONT)) {
		errorHandler(GENERAL_NONFATAL);
	}
}
