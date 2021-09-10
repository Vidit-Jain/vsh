#ifndef VSH_TOKENARRAY_H
#define VSH_TOKENARRAY_H
#include "string.h"
typedef struct tokenArray TokenArray;
struct tokenArray {
	String **args;
	unsigned int argCount;
	unsigned int maxSize;
};

TokenArray *newTokenArray();
TokenArray *newTokenArrayCustom(unsigned int size);

#endif // VSH_TOKENARRAY_H
