#include <stdio.h>      // For printf(), fgets()
#include <stdlib.h>     // For exit()
#include <string.h>     // For strtok(), strcmp(), strcspn()
#include <unistd.h>     // For fork(), execvp(), chdir()
#include <sys/wait.h>   // For wait()

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

// Split the input string into words and store in args[]
void parse_input(char* input, char** args) {
    int i = 0;
    args[i] = strtok(input, " \t\n");  // Cut out the first word
    while (args[i] != NULL && i < MAX_ARGS - 1) {
        args[++i] = strtok(NULL, " \t\n");  // Keep cutting out next words
    }
    args[i] = NULL;  // Null-terminate the array
}

int main() {
    char input[MAX_CMD_LEN];  // Stores the line the user types
    char* args[MAX_ARGS];     // Stores each word in the input line

    while (1) {
        // Show the shell prompt
        printf(":: ");
        if (!fgets(input, MAX_CMD_LEN, stdin)) {
            break;  // Ctrl+D exits the shell
        }

        // If user just presses Enter, skip
        if (input[0] == '\n') {
            continue;
        }

        // --- Handle built-in commands ---

        // Exit the shell
        if (strcmp(input, "exit\n") == 0) {
            break;
        }

        // Say hello
        else if (strcmp(input, "hello\n") == 0) {
            printf("Hello! Welcome to your custom shell.\n");
            continue;
        }

        // Show help
        else if (strcmp(input, "help\n") == 0) {
            printf("Built-in commands:\n");
            printf("  help   - Show this help message\n");
            printf("  hello  - Print a greeting\n");
            printf("  cd DIR - Change directory to DIR\n");
            printf("  exit   - Exit the shell\n");
            continue;
        }

        // Change directory (cd)
        else if (strncmp(input, "cd ", 3) == 0) {
            // Remove the newline at the end
            input[strcspn(input, "\n")] = '\0';

            // The directory is everything after "cd "
            char* dir = input + 3;

            // Try to change directory
            if (chdir(dir) != 0) {
                perror("cd");
            }

            continue;
        }

        // --- Run external command (like ls, pwd, echo) ---
        parse_input(input, args);  // Turn input into args

        pid_t pid = fork();  // Make a child process

        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            // In child process
            if (execvp(args[0], args) == -1) {
                perror("execvp");
            }
            exit(EXIT_FAILURE);  // Exit child on failure
        } else {
            // In parent process
            wait(NULL);  // Wait for child to finish
        }
    }

    printf("Exiting...\n");
    return 0;
}

