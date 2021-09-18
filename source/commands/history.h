#ifndef VSH_HISTORY_H
#define VSH_HISTORY_H
#include "../../globals.h"
#include "../processor/errorHandling.h"
#include "../utils/string.h"
#include "../utils/tokenArray.h"
#include "../utils/utils.h"
#define MAX_COMMAND_SIZE 255
#define MAX_HISTORY 20
void addHistory(String *command);
void commandHistory(TokenArray *tokens);
void initHistory();
#endif // VSH_HISTORY_H
