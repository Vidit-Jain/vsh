#ifndef VSH_EXECUTE_H
#define VSH_EXECUTE_H
#include "../commands/cd.h"
#include "../commands/echo.h"
#include "../commands/ls.h"
#include "../commands/pwd.h"
#include "../utils/tokenArray.h"
void executeCommand(TokenArray *tokens);
#endif // VSH_EXECUTE_H
