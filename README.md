# vsh
A basic shell implemented in C
# Usage
run `make`

and execute `./vsh`

## Assumptions
1. The length of each command is at max 255 characters
2. The name of the system is at max 255 characters
3. The path to the actual home of the user is at max 255 characters
4. pinfo won't be run on processes for which reading the executable path requires root access (although this is still handled by printing **Permission Denied**)
5. Path lengths are less than the **PATH_MAX** limit defined in _limits.h_ which on Linux is 4096
6. The history command is implemented with the assumption that it's the only program changing the history file during execution.

# Features
## Semi-colon
You can execute multiple shell commands in one line by separating them with `;`
## Display Prompt
The prompt displays the user's username along with the system name, and the directory they are currently working in,
assuming the location from which the user executed the shell as the home directory.
## Parsing arguments
The shell can correctly interpret the command sent, handling multiple tabs and spaces in between as well without any issues
## Builtin commands
There are 3 main builtin commands
### 1. cd
- The `cd` command allows you to change your current working directory. Beside just absolute paths, the command also handles
- `.` To denote the current directory
- `..` To denote the parent directory 
- `~` To denote the home directory
- `-` To denote the previous working directory
Upon entering no arguments, the `cd` command switches to your home directory
`cd` takes a max of one argument, giving invalid or an incorrect number of arguments will raise an error.
### 2. echo
- echo prints the arguments you entered to the command
### 3. pwd
- You can use the `pwd` command to print the absolute path of the directory you are currently in.
 
## ls
- The `ls` command helps you see all the directories in a directory.
- Passing no arguments executes `ls` on the current directory.
- You can use flags such as `-l`, `-a` to see more details of each file and to see hidden files as well.
- `ls` can be used on the current directory, multiple directories and even files.
## Running system commands
**Foreground processes** - You can execute normal commands such as `vi` with or without arguments as
a foreground process. You'll have to wait for the process to terminate before you can use your shell, 
or terminate it prematurely by using `Ctrl+C`.

**Background processes** - By appending `&` you can have a process run in the background, allowing you
to use the shell at the same time. You can run multiple processes, and executing a background process prints the PID of the new process.

## pinfo
- pinfo prints information about a certain process. 
- If no pid is mentioned, the command runs pinfo on the current shell
- Else it runs on the pid mentioned, giving details such as:
    1. pid number
    2. process status
    3. memory (in kb)
    4. executable path

## Finished background processes
When a background process is finished, the shell will print whether the process exited
normally or abnormally

## repeat
The `repeat` command allows you to repeat a certain command multiple times.

## history
The `history` command allows to see your history of commands (upto 20).
If no argument is passed, it'll print the last 10 commands used (not showing consecutively repeated commands)
Else, it's print the number of commands as specified by the argument, upto a maximum of 20 commands.
You can also cycle through your history by pressing the Up or Down arrow key to execute previously ran commands again.
## File Structure
```
vsh/
    Makefile - Contains makefile
    README.md - Contains description of commands and file structure
    vsh - The executable
    source/
        main.c      - Has the main function of the shell 
        globals.c - Has the global variables and constants
        commands/
            cd.c    - has functions used to implement cd
            echo.c  - has functions used to implement echo
            history.c - has functions used to impelement history
            ls.c    - has functions used to implement history
            pinfo.c - has functions use to implement pinfo
            pwd.c - has functions use to implement pwd
            repeat.c - has functions use to implement repeat
        processor/
            errorHandling.c - Handles errors in program
            exec.c  - Does the forking for running system commands
            execute.c - Runs the command passed by user
            prompt.c - Prints the prompt
            runningProcess.c - Keeps a list of running processes
            signalHandling.c - Contains the signal handlers used
            tokenize.c - Tokenizes the given input
        utils/
            string.c - Implements string data structure
            systemInfo.c - Has functions to get various information from system
            tokenArray.c - Implements array of strings
            utils.c - Misc functions used in program

```
