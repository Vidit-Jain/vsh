#ifndef VSH_RUNNINGPROCESSES_H
#define VSH_RUNNINGPROCESSES_H
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "errorHandling.h"
typedef struct process Process;
struct process {
	char *name;
	pid_t pid;
	struct process *nextProcess;
};
void initProcessList();
void addProcess(char *name, pid_t pid);
char *processName(pid_t pid);
void removeProcess(pid_t pid);
void exitShell();
#endif // VSH_RUNNINGPROCESSES_H
