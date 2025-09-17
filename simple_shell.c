#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;

    while (1)
    {
	    printf("#cisfun$ ");
	    fflush(stdout);

        nread = getline(&line, &len, stdin);
        
        if (nread == -1)
        {
            free(line);
            printf("\n");
            exit(0);
        }

        for (int i = 0; line[i]; i++)
        {
            if (line[i] == '\n')
            {
                line[i] = '\0';
                break;
            }
        }
        if (line[0] == '\0')
            continue;

        pid = fork();
        if (pid == 0)
        {
            if (execve(line, &line, environ) == -1)
            {
                perror("./shell: command not found");
                exit(1);
            }
        }
        else if (pid > 0)
        {
            wait(NULL);
        }
        else
        {
            perror("fork");
            exit(1);
        }
    }
    free(line);
    return 0;
}
