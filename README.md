# Custom-Shell
This is a simple command-line shell program written in C. It implements basic shell functionality like handling built-in commands (e.g., exit, cd, help, hello) and running external commands (e.g., ls, pwd, echo) using fork() and execvp(). The shell provides a minimalistic interface for interacting with the system through the command line.

Features

Interactive Command Prompt: The shell runs in a loop, presenting a :: prompt and waits for user input.

Built-in Commands:

exit: Exits the shell.

hello: Prints a greeting message.

help: Displays a list of available commands.

cd <directory>: Changes the current working directory to the specified directory.

External Commands: Executes system commands using execvp() in a child process.

Input Parsing: Uses strtok() to parse the user input into separate commands and arguments.

Forking and Waiting: Implements child processes using fork() to run commands, and wait() is used by the parent process to wait for child process completion.

Compilation

To compile the shell program, use gcc (GNU Compiler Collection) or any compatible C compiler:

gcc -o custom_shell custom_shell.c

Usage

After compilation, run the shell by executing:

./custom_shell


You will be presented with a :: prompt, where you can enter commands. Here are some examples:

To print a greeting:

:: hello


To change the directory to /home/user:

:: cd /home/user


To run a system command like ls:

:: ls -l


To exit the shell:

:: exit


To view the help message:

:: help

Built-in Commands
exit

Exits the shell.

:: exit

hello

Displays a greeting message.

:: hello

help

Displays a list of available commands.

:: help

cd <directory>

Changes the current working directory to the specified directory. If the directory does not exist or an error occurs, an error message is displayed.

:: cd /path/to/directory

How It Works

Input Handling: The shell waits for user input using fgets(). It reads up to MAX_CMD_LEN characters per command.

Built-in Commands:

If the user inputs a built-in command like exit, hello, help, or cd, the shell handles them directly.

cd uses the chdir() function to change directories.

External Commands:

For other commands, the input is parsed into arguments using strtok().

The shell uses fork() to create a child process and execvp() to execute the command in that child process.

The parent process waits for the child to finish using wait().

Error Handling:

If an invalid command is entered, or if the execution of a command fails (e.g., the command doesn't exist), the shell prints an error message.

Limitations

The shell does not handle advanced features like piping, input/output redirection, or background processes.

It does not support environment variables or command history.

It assumes that commands provided are either valid system commands or built-in ones.
