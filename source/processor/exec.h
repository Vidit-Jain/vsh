#ifndef VSH_EXEC_H
#define VSH_EXEC_H
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../utils/string.h"
#include "../utils/tokenArray.h"
#include "errorHandling.h"
void exec(TokenArray *tokens);
#endif // VSH_EXEC_H
