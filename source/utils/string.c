#include "string.h"

const unsigned int MAX_LEN = 256;
String *newString() {
	String *str1;
	str1 = (String *)malloc(sizeof(String));

	str1->maxSize = MAX_LEN;
	str1->str = (char *)malloc(str1->maxSize * sizeof(char));
	str1->str[0] = '\0';
	str1->length = 0;

	return str1;
}

String *newStringCustom(unsigned int size) {
	String *str1;
	str1 = (String *)malloc(sizeof(String));

	assert(size != 0);

	str1->maxSize = size;
	str1->str = (char *)malloc(size * sizeof(char));
	str1->str[0] = '\0';
	str1->length = 0;

	return str1;
}

void stringCopy(String *dest, String src) {

	if (dest == NULL)
		dest = newString();

	if (src.length >= dest->maxSize)
		dest->str = (char *)malloc((src.length + 1) * sizeof(char *));

	strcpy(dest->str, src.str);
	dest->length = src.length;
}

String *substring(String str, unsigned int startIndex,
				  unsigned int numberOfCharacters) {}

String *initString(const char *str) {
	unsigned int stringLength = strlen(str);
	String *filledString;
	if (stringLength >= MAX_LEN)
		filledString = newStringCustom(stringLength + 1);
	else
		filledString = newString();

	strcpy(filledString->str, str);
	filledString->length = stringLength;
}
unsigned int isEqualString(String str1, String str2) {
	return strcmp(str1.str, str2.str) == 0;
}

void emptyString(String *str) {
	str->str[0] = '\0';
	str->length = 0;
}
void updateLength(String *str) { str->length = strlen(str->str); }