# vsh
A unix shell implemented in C that supports many features, such as
 - Executing multiple shell commands in one line
 - Running background processes,
 - Piping support
 - I/O redirection
 - Signal handling to appropriately handle actions
 - Monitoring processes with customly made `pinfo` command
 - Custom commands to monitor statistics of the system like the amount of keyboard interrupts or dirty memory currently.

# Usage
1. run `make`

2. execute `./vsh`

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

**Usage:**

``` <abc@def:~> cd <directory> ```

### 2. echo
- echo prints the arguments you entered to the command
 
**Usage:**

``` <abc@def:~> echo <message> ```

This will display `<message>` in the terminal.
### 3. pwd
- You can use the `pwd` command to print the absolute path of the directory you are currently in.


**Usage:**

``` <abc@def:~> pwd ```

Executing this will display the current absolute directory.

## ls
- The `ls` command helps you see all the directories in a directory.
- Passing no arguments executes `ls` on the current directory.
- You can use flags such as `-l`, `-a` to see more details of each file and to see hidden files as well.
- `ls` can be used on the current directory, multiple directories and even files.

**Usage:**

``` <abc@def:~> ls <flags optional> <directory optional> ```

Based on the flags and the directory specified, `ls` will display the directory information. 
## Running system commands
**Foreground processes** - You can execute normal commands such as `vi` with or without arguments as
a foreground process. You'll have to wait for the process to terminate before you can use your shell, 
or terminate it prematurely by using `Ctrl+C`.

**Usage:** 

``` <abc@def:~> external-command arg1 arg2 ...  ```

This will execute the external command with the arguments specified. 

**Background processes** - By appending `&` you can have a process run in the background, allowing you
to use the shell at the same time. You can run multiple processes, and executing a background process prints the PID of the new process.

**Usage:** 

``` <abc@def:~> command1 &  ```

This will execute the command in the background
## pinfo
- pinfo prints information about a certain process. 
- If no pid is mentioned, the command runs pinfo on the current shell
- Else it runs on the pid mentioned, giving details such as:
    1. pid number
    2. process status
    3. memory (in kb)
    4. executable path

**Usage:**

``` <abc@def:~> pinfo <pid>  ```

This will print the information of the process with `pid`, or info of the current process if no pid is specified.

## Finished background processes
When a background process is finished, the shell will print whether the process exited
normally or abnormally

## repeat
The `repeat` command allows you to repeat a certain command multiple times.

**Usage:**

``` <abc@def:~> repeat <number> <command1> ```

Here, command1 will be executed `<number>` times.
## history
The `history` command allows to see your history of commands (upto 20).
If no argument is passed, it'll print the last 10 commands used (not showing consecutively repeated commands)
Else, it's print the number of commands as specified by the argument, upto a maximum of 20 commands.
You can also cycle through your history by pressing the Up or Down arrow key to execute previously ran commands again.

**Usage:**

``` <abc@def:~> history <number> ```

or 


``` <abc@def:~> history ```
## I/O Redirection
The shell supports I/O redirection. You can specify which file you want to take input from or give
output to using `>`, `<`, `>>` to specify output (rewrite), input or output(append) respectively.

The shell supports specifying the input and output files in any order

**Usage**:

``` <abc@def:~> command > output.txt < input.txt```

Here, we are giving content of `input.txt` as input to the command, and redirect the output of the command
to `output.txt`.

## Command Pipelines
The shell provides piping functionality as well. Hence, you can redirect output of one command to another
using pipes. The pipes work with not only external commands, but builtin commands as well.

**Usage:** 

```<abc@def:~> <command 1> | <command 2>```


To pipe output of command1 as input for command 2.

The piping can work along with I/O redirection as well.

**Usage:**

```<abc@def:~> <command 1> < input.txt | <command 2> > output.txt```

Here, we are using `input.txt` as input to command1, and sent it's output to command 2 as input, and redirecting
output of command 2 to `output.txt`

## jobs
You can use this command to check all the currently running background processes. You can specify flags
`-s`, `-r` if you only want to see stopped or running background processes respectively.

**Usage:**

```<abc@def:~> jobs <flags>```

This will display the status of each job from the list of jobs specified by flags, and the number assigned to them by the shell  

**Output Example:**

```
[2] Running gedit [50386]
[1] Stopped zathura [50370]
```
The jobs are listed alphabetically by the command name. The numbering given to the jobs of the shell are given
in order of their creation, and are dynamic, i.e Say we have 5 processes 1,2,3,4,5. If process 3 ends, the jobs
with id 4, 5 will be shifted to 3,4. If a job is created later, it will be given the id 5.

## sig
You can use the command to send a signal to a job

**Usage:**

```<abc@def:~> sig <job-number> <signum>```

This will send `signum` to process which has `job-number` as their job number.

## bg
You can bring a stopped background process to running


**Usage:**

```<abc@def:~> bg <job-number>```

Brings the stopped background process with job-number `job-number` to running.

## fg
You can bring a background process to the foreground 

**Usage:**

```<abc@def:~> fg <job-number>```

Brings the background process with job-number `job-number` to foreground.

## replay
Allows you to replay a command at intervals for a specified period

**Usage:**

```<abc@def:~> replay -command <command> -interval <interval> -period <period>```

The flags can be in any order. The command specified will be executed at intervals of
`<interval>` till `<period>` seconds are over.

## baywatch
Can be used to check either the number of keyboard controller interrupts, the pid of the latest process created
or the amount of dirty memory in the system currently at a periodic amount of time.

**Usage:**

```<abc@def:~> baywatch -n <interval> command ```

Flag can come before or after command. Command can be `interrupt`, `newborn`, or `dirty`. This will execute the 
respective command at intervals of `<interval>`, and you can terminate the program by pressing `q` in your terminal.

## Signal-handling
`Ctrl + Z` - Suspends the current running foreground process and puts it into background.

`Ctrl + C` - Terminates the foreground process of the shell.

`Ctrl + D` - Logs you out of the shell, but doesn't close the terminal
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
            baywatch.c - contains functions to implement baywatch
            bg.c - contains functions to implement bg
            cd.c    - has functions used to implement cd
            echo.c  - has functions used to implement echo
            fg.c - contains functions to implemented fg
            history.c - has functions used to impelement history
            jobs.c - contains functions related to the jobs command
            ls.c    - has functions used to implement history
            pinfo.c - has functions use to implement pinfo
            pwd.c - has functions use to implement pwd
            repeat.c - has functions use to implement repeat
            replay.c - parses the replay command when called
            sig.c - contains functions which implement the sig command
        processor/
            errorHandling.c - Handles errors in program
            exec.c  - Does the forking for running system commands
            execute.c - Runs the command passed by user, implements piping
            parsing.c - Function to parse I/O redirection files specified
            prompt.c - Prints the prompt
            redirection.c - Redirects I/O given input and output files
            runningProcess.c - Keeps a list of running processes
            signalHandling.c - Contains the signal handlers used
            tokenize.c - Tokenizes the given input
        utils/
            string.c - Implements string data structure
            systemInfo.c - Has functions to get various information from system
            tokenArray.c - Implements array of strings
            utils.c - Misc functions used in program

```
