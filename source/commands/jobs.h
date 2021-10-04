#ifndef VSH_JOBS_H
#define VSH_JOBS_H
#include "../processor/runningProcesses.h"
#include "../utils/tokenArray.h"
#include "../utils/utils.h"
#include <stdlib.h>
#include <string.h>
typedef struct job Job;
struct job {
	char *name;
	int job_no;
	int state;
	pid_t pid;
};
void commandJobs(TokenArray *tokens);
#endif // VSH_JOBS_H
