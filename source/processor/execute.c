#include "execute.h"
void execute(TokenArray* tokens) {
    if (tokens->argCount == 0) return;
    if (isEqualString(*tokens->args[0], *initString("cd"))) {
        commandCd(tokens);
    }
}