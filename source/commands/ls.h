#ifndef VSH_LS_H
#define VSH_LS_H
#include "../utils/tokenArray.h"
String *filePermissions(String* filePath);
void commandLS(TokenArray *tokens);
#endif //VSH_LS_H
