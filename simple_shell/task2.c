#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGV_LENGTH 10

int main() {
    char input[MAX_INPUT_LENGTH];
    char *argv[MAX_ARGV_LENGTH];
    int status;
    char *token;
    pid_t pid;
    int argc;

    while (1) {
        printf("$ ");
        fflush(stdout);
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        token = strtok(input, " ");
        argc = 0;
        while (token != NULL && argc < MAX_ARGV_LENGTH - 1) {
            argv[argc] = token;
            argc++;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            
            execvp(argv[0], argv);
            perror(argv[0]);
            exit(EXIT_FAILURE);
        } else {
            
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

