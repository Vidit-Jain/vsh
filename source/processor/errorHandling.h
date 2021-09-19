#ifndef VSH_ERRORHANDLING_H
#define VSH_ERRORHANDLING_H
#define BAD_MALLOC 1
#define INVALID_SIZE 2
#define GENERAL_FATAL 15
#define GENERAL_NONFATAL 22
#define INCORRECT_ARGC 23
#define INVALID_ARGS 24
#include <stdio.h>

#include "../utils/string.h"
#include "runningProcesses.h"
void errorHandler(int code);
#endif // VSH_ERRORHANDLING_H
