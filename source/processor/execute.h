#ifndef VSH_EXECUTE_H
#define VSH_EXECUTE_H
#include "../commands/cd.h"
#include "../commands/echo.h"
#include "../commands/ls.h"
#include "../commands/pwd.h"
#include "../commands/repeat.h"
#include "../utils/tokenArray.h"
#include "exec.h"
#include "tokenize.h"
void executeCommand(TokenArray *tokens);
void executeLine(TokenArray *tokens, String input);
#endif // VSH_EXECUTE_H
