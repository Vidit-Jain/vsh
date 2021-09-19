#include "tokenArray.h"

const unsigned int MAX_ARGS = 256;
// Creates new token array
TokenArray *newTokenArray() {
	TokenArray *tokens = (TokenArray *)malloc(sizeof(TokenArray));
	if (tokens == NULL)
		errorHandler(BAD_MALLOC);

	tokens->args = (String **)malloc(MAX_ARGS * sizeof(String *));
	if (tokens->args == NULL)
		errorHandler(BAD_MALLOC);
	tokens->maxSize = MAX_ARGS;
	return tokens;
}

// Creates new token array with custom size
TokenArray *newTokenArrayCustom(unsigned int size) {
	TokenArray *tokens = (TokenArray *)malloc(sizeof(TokenArray));
	if (tokens == NULL)
		errorHandler(BAD_MALLOC);

	if (size == 0)
		errorHandler(INVALID_SIZE);
	tokens->args = (String **)malloc(size * sizeof(String *));
	if (tokens->args == NULL)
		errorHandler(BAD_MALLOC);
	tokens->maxSize = size;
	return tokens;
}
// Copy one token array and create a new copy
TokenArray *duplicateTokenArray(TokenArray *tokens) {
	TokenArray *duplicate = newTokenArrayCustom(tokens->maxSize);
	duplicate->argCount = tokens->argCount;
	for (int i = 0; i < duplicate->argCount; i++) {
		duplicate->args[i] = initString(tokens->args[i]->str);
	}
	return duplicate;
}