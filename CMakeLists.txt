cmake_minimum_required(VERSION 3.20)
project(vsh C)

set(CMAKE_C_STANDARD 11)

add_executable(vsh
        source/utils/string.c source/utils/string.h source/utils/systemInfo.c source/utils/systemInfo.h main.c source/processor/prompt.c source/processor/prompt.h globals.c globals.h source/utils/tokenArray.c source/utils/tokenArray.h source/processor/tokenize.c source/processor/tokenize.h source/processor/execute.c source/processor/execute.h source/commands/cd.c source/commands/cd.h source/commands/echo.c source/commands/echo.h source/commands/pwd.c source/commands/pwd.h source/commands/pinfo.c source/commands/pinfo.h source/commands/ls.c source/commands/ls.h source/processor/exec.c source/processor/exec.h source/commands/repeat.c source/commands/repeat.h)
