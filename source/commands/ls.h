#ifndef VSH_LS_H
#define VSH_LS_H
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

#include "../globals.h"
#include "../processor/errorHandling.h"
#include "../utils/tokenArray.h"
#include "../utils/utils.h"
#define SIX_MONTHS 15780000
String *filePermissions(String *filePath);
void commandLS(TokenArray *tokens);
#endif // VSH_LS_H
