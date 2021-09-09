#ifndef VSH_STRING_H
#define VSH_STRING_H
#include <assert.h>
#include <stdlib.h>
#include <string.h>
typedef struct string String;
struct string {
	char *str;
	unsigned int length;
	unsigned int maxSize;
};

String *newString();
String *newStringCustom(unsigned int size);
void stringCopy(String *dest, String src);
String *substring(String str, unsigned int startIndex,
				  unsigned int numberOfCharacters);
String *initString(const char *str);
void emptyString(String *str);
void updateLength(String *str);

#endif // VSH_STRING_H
