#ifndef VSH_GLOBALS_H
#define VSH_GLOBALS_H
#include "source/utils/string.h"
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

extern String *homePath;

extern String *currentPath;

extern String *displayPath;
extern String *previousPath;

extern String *username;
extern String *systemName;

extern String *actualHome;
#endif // VSH_GLOBALS_H
