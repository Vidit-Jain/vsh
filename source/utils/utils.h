#ifndef VSH_UTILS_H
#define VSH_UTILS_H
#include <grp.h>
#include <sys/stat.h>

#include "../processor/errorHandling.h"
#include "../processor/runningProcesses.h"
#include "systemInfo.h"
#include "tokenArray.h"
void initInfo();
int isNumber(String *number);
unsigned long toNumber(String *number);
int folderExists(String path);
int fileExists(String path);
String *getUser(uid_t uid);
String *getGroup(gid_t gid);
#endif // VSH_UTILS_H
