#ifndef VSH_EXECUTE_H
#define VSH_EXECUTE_H
#include "../commands/cd.h"
#include "../commands/echo.h"
#include "../utils/tokenArray.h"
#include "../commands/pwd.h"
void execute(TokenArray *tokens);
#endif // VSH_EXECUTE_H
