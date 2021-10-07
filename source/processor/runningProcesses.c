#include "runningProcesses.h"
Process *head;
int totalProcesses = 0;
void initProcessList() { head = NULL; }
int getTotalProcesses() { return totalProcesses; }
// Create a process to be added into the list of running processes
Process *createProcess(char *name, pid_t pid) {
	Process *p = (Process *)malloc(sizeof(Process));
	if (p == NULL)
		errorHandler(BAD_MALLOC);
	p->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
	if (p->name == NULL)
		errorHandler(BAD_MALLOC);
	strcpy(p->name, name);
	p->pid = pid;
	p->nextProcess = NULL;
	return p;
}

// Add a process to the list of running processes
void addProcess(char *name, pid_t pid) {
	Process *process = createProcess(name, pid);
	process->nextProcess = head;
	head = process;
	totalProcesses++;
}

// Given a pid, find the name of the process, return NULL if not found
char *processName(pid_t pid) {
	Process *traverse = head;
	while (traverse != NULL) {
		if (traverse->pid == pid) {
			return traverse->name;
		}
		traverse = traverse->nextProcess;
	}
	return NULL;
}
void exitShell() {
	while (head != NULL) {
		pid_t pid = head->pid;
		kill(pid, SIGTERM);
		removeProcess(pid);
	}
	exit(0);
}
// Remove a process from list of processes
void removeProcess(pid_t pid) {
	if (head == NULL)
		return;
	if (head->pid == pid) {
		Process *temp = head;
		head = head->nextProcess;
		free(temp);
		totalProcesses--;
		return;
	}
	Process *prev = head;
	Process *curr = head->nextProcess;
	while (curr != NULL) {
		if (curr->pid == pid) {
			prev->nextProcess = curr->nextProcess;
			free(curr);
			totalProcesses--;
			break;
		}
		prev = curr;
		curr = curr->nextProcess;
	}
}

void currentProcesses(char *processNames[], pid_t ids[]) {
	Process *traverse = head;
	/* Filling the array in reverse as we enter processes like a stack in the
	 * Linked list
	 */
	int index = totalProcesses - 1;
	while (traverse != NULL) {
		int nameLength = (int)strlen(traverse->name) + 1;
		processNames[index] = (char *)malloc(nameLength * sizeof(char));
		strcpy(processNames[index], traverse->name);

		ids[index] = traverse->pid;
		traverse = traverse->nextProcess;
		index--;
	}
}
pid_t getJob(int job_no) {
	// Checks if job_number exists
	if (job_no > totalProcesses || job_no <= 0) {
		return -1;
	}
	Process *traverse = head;
	// Done numbering in reverse, hence we must do it this way
	for (int i = 0; i < totalProcesses - job_no; i++) {
		traverse = traverse->nextProcess;
	}
	return traverse->pid;
}