#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void) {
    char *input_buffer;
    char *program;
    size_t buffer_size = BUFFER_SIZE;
    ssize_t line_size;
    pid_t pid;
    int status;

    while (1) {
        input_buffer = (char *)malloc(buffer_size * sizeof(char));
        if (input_buffer == NULL) {
            perror("Error, malloc failed");  
            exit(EXIT_FAILURE);
        }

        printf("$ ");
        line_size = getline(&input_buffer, &buffer_size, stdin);
        if (line_size == -1) {
            printf("\n");
            free(input_buffer);
            exit(EXIT_SUCCESS);
        }

        if (input_buffer[line_size - 1] == '\n') {
            input_buffer[line_size - 1] = '\0';
        }

        program = strtok(input_buffer, " ");
        if (program == NULL) {
            free(input_buffer);
            continue;
        }

        pid = fork();
        if (pid < 0) {
            perror("Error"); 
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            execlp(program, program, NULL);
            perror("Error");               exit(EXIT_FAILURE);
        } else {
            waitpid(pid, &status, 0);
        }

        free(input_buffer);
    }

    return 0;
}
