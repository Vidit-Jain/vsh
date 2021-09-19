#ifndef VSH_STRING_H
#define VSH_STRING_H
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../processor/errorHandling.h"
typedef struct string String;
struct string {
	char *str;
	unsigned int length;
	unsigned int maxSize;
};

String *newString();
String *newStringCustom(unsigned int size);
void stringCopy(String *dest, String src);
String *initString(const char *str);
void updateLength(String *str);
void concatenate(String *str1, String *str2);
unsigned int isEqualString(String str1, String str2);

#endif // VSH_STRING_H
