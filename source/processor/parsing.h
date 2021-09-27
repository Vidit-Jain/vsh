#ifndef VSH_PARSING_H
#define VSH_PARSING_H
#include "../utils/string.h"
#include "../utils/tokenArray.h"
int parseRedirection(TokenArray *tokens, String **inputFile,
					 String **outputFile, int *outputStyle);
#endif // VSH_PARSING_H
