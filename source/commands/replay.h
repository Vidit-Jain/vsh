#ifndef VSH_REPLAY_H
#define VSH_REPLAY_H
#include <string.h>

#include "../utils/tokenArray.h"
#include "../utils/utils.h"
TokenArray *commandReplay(TokenArray *tokens, int *interval, int* period, int *error);
#endif // VSH_REPLAY_H
