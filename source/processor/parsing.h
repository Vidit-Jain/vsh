#ifndef VSH_PARSING_H
#define VSH_PARSING_H
#include "../utils/string.h"
#include "../utils/tokenArray.h"
int checkRedirection(String **inputFile, String **outputFile, TokenArray *tokens);
#endif //VSH_PARSING_H
