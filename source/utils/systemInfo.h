#ifndef VSH_SYSTEMINFO_H
#define VSH_SYSTEMINFO_H
#include <pwd.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

#include "../../globals.h"
#include "string.h"


String *getUsername();
String *getSystemName();
String *setHomePath();
String *getCurrentPath();
unsigned int getDepth(String path);
unsigned int inHomeDirectory();
void updateDisplayPath();

#endif // VSH_SYSTEMINFO_H
