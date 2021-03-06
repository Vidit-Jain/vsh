#include "string.h"

const unsigned int MAX_LEN = 256;
// Initialize a new string
String *newString() {
	String *str1;
	str1 = (String *)malloc(sizeof(String));
	if (str1 == NULL)
		errorHandler(BAD_MALLOC);

	str1->maxSize = MAX_LEN;
	str1->str = (char *)malloc(str1->maxSize * sizeof(char));
	if (str1->str == NULL)
		errorHandler(BAD_MALLOC);
	str1->str[0] = '\0';
	str1->length = 0;

	return str1;
}
// Create a string with a custom size
String *newStringCustom(unsigned int size) {
	String *str1;
	str1 = (String *)malloc(sizeof(String));
	if (str1 == NULL)
		errorHandler(BAD_MALLOC);

	if (size == 0)
		errorHandler(INVALID_SIZE);
	str1->maxSize = size;
	str1->str = (char *)malloc(size * sizeof(char));
	if (str1->str == NULL)
		errorHandler(BAD_MALLOC);
	str1->str[0] = '\0';
	str1->length = 0;

	return str1;
}

// Copy one string into another
void stringCopy(String *dest, String src) {

	if (dest == NULL)
		dest = newString();

	if (src.length >= dest->maxSize) {
		dest->str = (char *)malloc((src.length + 1) * sizeof(char *));
		if (dest->str == NULL)
			errorHandler(BAD_MALLOC);
	}

	strcpy(dest->str, src.str);
	dest->length = src.length;
}
// Takes a char* and copies the string and creates a String
String *initString(const char *str) {
	unsigned int stringLength = strlen(str);
	String *filledString;
	if (stringLength >= MAX_LEN)
		filledString = newStringCustom(stringLength + 1);
	else
		filledString = newString();

	strcpy(filledString->str, str);
	filledString->length = stringLength;
	return filledString;
}
// Checks if two strings are equal
unsigned int isEqualString(String str1, String str2) {
	return strcmp(str1.str, str2.str) == 0;
}
// Concatenate one string to another
void concatenate(String *str1, String *str2) {
	if (str1->length + str2->length + 1 > str1->maxSize) {
		String *temp = initString(str1->str);
		str1 = newStringCustom(str1->length + str2->length + 1);
		stringCopy(str1, *temp);
	}
	strcat(str1->str, str2->str);
	updateLength(str1);
}

// Update string->length variable
void updateLength(String *str) { str->length = strlen(str->str); }