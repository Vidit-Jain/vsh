#ifndef VSH_REDIRECTION_H
#define VSH_REDIRECTION_H
#include "../utils/string.h"
#include "errorHandling.h"
#include <fcntl.h>
int setOutputRedirect(String *outputFile, int outputStyle);
int resetOutputRedirect();
int setInputRedirect(String *inputFile);
int resetInputRedirect();
#endif // VSH_REDIRECTION_H
