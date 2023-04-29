#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <stdbool.h>

#define MAX_ARGS 256
#define MAX_command_LEN 1024

// function signatures
void sigintHandler();

bool getUserInput(char *command, int max_command_len);

void processCommand(char *command);

void executeCommand(char **args, int input_fd, int output_fd);


/**
 * this is a shell program that can execute terminal commands
 * this part of the assignment shows how to use fork,exec,wait,signals,pipes,redirect
 * @return 0
 */
int main() {
    signal(SIGINT, sigintHandler);
    char command[MAX_command_LEN];
    while (true) {
        printf("315800961_318417763_shell$ ");
        fflush(stdout);
        if (!getUserInput(command, MAX_command_LEN)) {
            break;
        }
        processCommand(command);
    }

    return 0;
}

/**
 * blocks CTRL + c (SIGINT) commands to close the program
 */
void sigintHandler() {
    printf("\nCTRL + c not allowed type exit to close the program.\n");
    fflush(stdout);
}

/**
 *  read the command to execute from stdin
 * @param command user input
 * @param max_command_len the total size of the command
 * @return true on success and false on failure
 */
bool getUserInput(char *command, int max_command_len) {
    if (fgets(command, max_command_len, stdin) == NULL) {
        return false;
    }

    size_t command_len = strlen(command);
    if (command[command_len - 1] == '\n') {
        command[command_len - 1] = '\0';
    }
    return true;
}

/**
 * process a command checks the entire string to see if it have >, >> or pipes and separate it
 * each token or part of the command is seperated by " " (empty space)
 *
 * @param command the command to process
 */
void processCommand(char *command) {
    char *token;
    char *args[MAX_ARGS];
    int arg_count = 0;
    int input_fd = STDIN_FILENO;
    int output_fd = STDOUT_FILENO;

    token = strtok(command, " ");
    while (token != NULL) {
        if (strcmp(token, "|") == 0) {
            int pipe_fds[2];
            if (pipe(pipe_fds) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            executeCommand(args, input_fd, pipe_fds[1]);
            close(pipe_fds[1]);
            input_fd = pipe_fds[0];
            arg_count = 0;
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " ");
            output_fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
            if (output_fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(token, ">>") == 0) {
            token = strtok(NULL, " ");
            output_fd = open(token, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
            if (output_fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(token, "exit") == 0) {
            exit(EXIT_SUCCESS);
        } else {
            args[arg_count++] = token;
        }

        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;
    executeCommand(args, input_fd, output_fd);
}

/**
 * Forks a new process to execute a command with the given arguments
 * @param args: An array of strings representing the command and its arguments
 * @param input_fd: The file descriptor for the input stream to the command
 * @param output_fd: The file descriptor for the output stream from the command
 */
void executeCommand(char **args, int input_fd, int output_fd) {
    pid_t pid = fork();
    if (pid == 0) {
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
    } else {
        wait(NULL);
    }
}