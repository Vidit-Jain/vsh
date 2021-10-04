#include "jobs.h"
// Used to sort jobs alphabetically by command name
int comparator(const void* a, const void* b) {
	return strcmp(((Job*)a)->name, ((Job*)b)->name);
}
/* Flags
 * 1 - print running processes
 * 2 - print stopped processes
 */
int checkFlagsJobs(TokenArray *tokens) {
	char *args[tokens->argCount];
	for (int i = 0; i < tokens->argCount; i++) {
		args[i] = tokens->args[i]->str;
	}
	int flags = 0;
	int opt;
	while ((opt = getopt((int)tokens->argCount, args, ":sr")) != -1) {
		switch (opt) {
		case 's': flags |= 2; break;
		case 'r': flags |= 1; break;
		case '?':
			errorHandler(INVALID_ARGS);
			flags = -1;
			break;
		default: errorHandler(INVALID_ARGS);
		}
		if (flags == -1)
			break;
	}
	optind = 0;
	if (flags == 0) flags = 2;
	return flags;
}
void printJobs(int flags) {

	int totalProcesses = getTotalProcesses();

	char* processNames[totalProcesses];
	pid_t ids[totalProcesses];

	currentProcesses(processNames, ids);

	// Made array of structs to sort processes easily
	Job jobs[totalProcesses];
	for (int i = 0; i < totalProcesses; i++) {
		jobs[i].name = processNames[i];
		jobs[i].job_no = i + 1;
		jobs[i].pid = ids[i];
		String* stateLetter = getState(jobs[i].pid);
		if (strcmp(stateLetter->str, "S") == 0) {
			jobs[i].state = 0;
		}
		else jobs[i].state = 1;
	}

	// Sorting the processes
	qsort((void*) jobs, totalProcesses, sizeof(jobs[0]), comparator);

	// Printing the processes
	for (int i = 0; i < totalProcesses; i++) {
		// Print if we should print running processes.
		if ((flags & 1) && jobs[i].state == 1)
			printf("[%d] %s %s [%d]\n", jobs[i].job_no, jobs[i].state ? "Running" : "Stopped", jobs[i].name, jobs[i].pid);
		// Print if we should print stopped processes.
		if ((flags & 2) && jobs[i].state == 0)
			printf("[%d] %s %s [%d]\n", jobs[i].job_no, jobs[i].state ? "Running" : "Stopped", jobs[i].name, jobs[i].pid);
	}
}
void commandJobs(TokenArray* tokens) {
	int flags = checkFlagsJobs(tokens);
	if (flags == -1) return;
	printJobs(flags);
}