#ifndef VSH_GLOBALS_H
#define VSH_GLOBALS_H
#include "source/utils/string.h"
extern unsigned int homePathDepth;
extern String* homePath;

extern unsigned int currentPathDepth;
extern String* currentPath;

extern String* displayPath;
extern String* previousPath;
#endif //VSH_GLOBALS_H
