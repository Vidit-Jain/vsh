#ifndef VSH_SYSTEMINFO_H
#define VSH_SYSTEMINFO_H
#include "string.h"
#include <pwd.h>
#include <unistd.h>

String *getUsername();
String *getSystemName();

#endif // VSH_SYSTEMINFO_H
