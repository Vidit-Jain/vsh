#ifndef VSH_PINFO_H
#define VSH_PINFO_H
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "../utils/tokenArray.h"
#include "../utils/string.h"
#include "../utils/tokenArray.h"
#include "../utils/utils.h"
void pinfo(pid_t pid);
void commandPinfo(TokenArray *tokens);
#endif // VSH_PINFO_H
