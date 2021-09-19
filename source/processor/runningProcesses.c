#include "runningProcesses.h"
Process *head;
void initProcessList() { head = NULL; }
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

void addProcess(char *name, pid_t pid) {
	Process *process = createProcess(name, pid);
	process->nextProcess = head;
	head = process;
}

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

void removeProcess(pid_t pid) {
	if (head == NULL)
		return;
	if (head->pid == pid) {
		Process *temp = head;
		head = head->nextProcess;
		free(temp);
		return;
	}
	Process *prev = head;
	Process *curr = head->nextProcess;
	while (curr != NULL) {
		if (curr->pid == pid) {
			prev->nextProcess = curr->nextProcess;
			free(curr);
			break;
		}
		prev = curr;
		curr = curr->nextProcess;
	}
}