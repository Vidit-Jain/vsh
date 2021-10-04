#ifndef VSH_SIG_H
#define VSH_SIG_H
#include "../processor/errorHandling.h"
#include "../processor/runningProcesses.h"
#include "../utils/tokenArray.h"
#include "../utils/utils.h"
#include <signal.h>

void commandSig(TokenArray *tokens);
#endif // VSH_SIG_H
