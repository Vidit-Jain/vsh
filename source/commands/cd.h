#ifndef VSH_CD_H
#define VSH_CD_H
#include <stdio.h>
#include <unistd.h>

#include "../globals.h"
#include "../processor/errorHandling.h"
#include "../utils/systemInfo.h"
#include "../utils/tokenArray.h"

void commandCD(TokenArray *tokens);
#endif // VSH_CD_H
