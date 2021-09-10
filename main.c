#include "source/processor/prompt.h"
int main() {
    setHomePath();
    getCurrentPath();
    printPrompt();
    chdir("..");
    chdir("..");
    currentPathDepth--;
    currentPathDepth--;
    getCurrentPath();
    printPrompt();

    chdir("vsh");
    currentPathDepth++;
    chdir("cmake-build-debug");
    getCurrentPath();
    printPrompt();
}