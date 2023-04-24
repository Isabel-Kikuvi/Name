#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main() {
    char *input = NULL; *input_copy = NULL;
    char *argv;
    int status;
    char *token, *delim = " \n";
    size_t n = 0;
    pid_t pid;
    int argc;

    while (1) {
        printf("$ ");
        
        if (getline(&input, &n, stdin) == -1) 
	{
            break;
        }

        input_copy = strdup(input);
        token = strtok(input, delim);
	argc = 0;

        while (token) 
	{
            argv[argc] = token;
            argc++;
            token = strtok(NULL, delim);
        }
        argv[argc] = NULL;

        pid = fork();

        if (pid < 0) 
	{
            perror("fork");
            exit(EXIT_FAILURE);
        } 
	else if (pid == 0) 
	{
	    execvp(argv[0], argv);
            perror(argv[0]);
            exit(EXIT_FAILURE);
        } 
	else 
	{
            
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

