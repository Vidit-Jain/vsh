#ifndef VSH_EXEC_H
#define VSH_EXEC_H
#include <f2fs_fs.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../utils/string.h"
#include "../utils/tokenArray.h"
#include "errorHandling.h"
#include "prompt.h"
#include "runningProcesses.h"
#include "signalHandling.h"

void closePipes();
void exec(TokenArray *tokens, bool pipeInput, bool pipeOutput);
#endif // VSH_EXEC_H
