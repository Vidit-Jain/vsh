#ifndef VSH_EXECUTE_H
#define VSH_EXECUTE_H
#include "../commands/baywatch.h"
#include "../commands/bg.h"
#include "../commands/cd.h"
#include "../commands/echo.h"
#include "../commands/fg.h"
#include "../commands/history.h"
#include "../commands/jobs.h"
#include "../commands/ls.h"
#include "../commands/pinfo.h"
#include "../commands/pwd.h"
#include "../commands/repeat.h"
#include "../commands/replay.h"
#include "../commands/sig.h"
#include "../utils/tokenArray.h"
#include "exec.h"
#include "parsing.h"
#include "redirection.h"
#include "tokenize.h"

void executeLine(TokenArray *tokens, String input);
#endif // VSH_EXECUTE_H
