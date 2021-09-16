#ifndef VSH_PWD_H
#define VSH_PWD_H
#include <stdio.h>

#include "../../globals.h"
#include "../processor/errorHandling.h"
#include "../commands/pwd.h"
#include "../utils/tokenArray.h"
void commandPWD(TokenArray *tokens);
#endif // VSH_PWD_H
