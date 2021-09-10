#ifndef VSH_GLOBALS_H
#define VSH_GLOBALS_H
#include "source/utils/string.h"
#define MIN(A, B) ((A < B) ? A : B)
#define MAX(A, B) ((A < B) ? A : B)
extern unsigned int homePathDepth;
extern String* homePath;

extern unsigned int currentPathDepth;
extern String* currentPath;

extern String* displayPath;
#endif //VSH_GLOBALS_H
