#include "repeat.h"
int isNumber(TokenArray *tokens) {
    String *repeats = tokens->args[1];
    for (int i = 0; i < repeats->length; i++) {
        if (repeats->str[i] < '0' || repeats->str[i] > '9') return 0;
    }
    return 1;
}
int toNumber(TokenArray *tokens) {
    String *repeats = tokens->args[1];
    int number = 0;
    for (int i = (int)repeats->length - 1; i >= 0; i--) {
        number *= 10;
        number += repeats->str[i] - '0';
    }
    return number;
}
int commandRepeat(TokenArray *tokens) {
    if (tokens->argCount < 2) {
        printf("repeat: Incorrect number of arguments\n");
        return -1;
    }
    if (!isNumber(tokens)) {
        printf("repeat: Enter a number along with the command repeat\n");
        return -1;
    }
    int repeats = toNumber(tokens);
    return repeats;
}