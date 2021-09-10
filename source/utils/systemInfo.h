#ifndef VSH_SYSTEMINFO_H
#define VSH_SYSTEMINFO_H
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

#include "../../globals.h"
#include "string.h"

String *getUsername();
String *getSystemName();
String *setHomePath();
String *getCurrentPath();
unsigned int getDepth(String path);
unsigned int inHomeDirectory();
void updateDisplayPath();
void goToCurrentPath();

#endif // VSH_SYSTEMINFO_H
