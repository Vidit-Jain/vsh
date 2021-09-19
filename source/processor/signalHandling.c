#include "signalHandling.h"
// Terminate child process`
void sigint_handler() { exit(0); }

/* On child termination find the child process nameo
 * and print that the process has finished execution
 */
void child_handler() {
	int code;
	pid_t pid;
	while ((pid = waitpid(-1, &code, WNOHANG | WUNTRACED)) > 0) {
		char *process = processName(pid);
		if (process == NULL)
			continue;
		char *status =
			(WIFEXITED(code) || WIFSTOPPED(code)) ? "normally" : "abnormally";
		fprintf(stderr, "\n%s with pid %d exited %s\n", process, pid, status);
		removeProcess(pid);
		printPrompt();
		fflush(stderr);
	}
}
