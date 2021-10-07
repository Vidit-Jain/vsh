#include "fg.h"
void commandFg(TokenArray *tokens) {
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

	// Returns -1 if job_no doesn't exist
	if (pid == -1) {
		fprintf(stderr, "\033[0;31m");
		fprintf(stderr, "Invalid job number\n");
		fprintf(stderr, "\033[0m");
		return;
	}

	if (kill(pid, SIGCONT)) {
		errorHandler(GENERAL_NONFATAL);
	}
	// Wait normally like how we do in exec
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	tcsetpgrp(STDIN_FILENO, pid);

	int status;
	waitpid(pid, &status, WUNTRACED);

	tcsetpgrp(STDIN_FILENO, getpgrp());
	signal(SIGTTOU, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	// Remove pid as it was once a bg process
	removeProcess(pid);
}
