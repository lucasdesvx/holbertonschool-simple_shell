#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int i;

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
        for (i = 0; line[i]; i++)
        {
            if (line[i] == '\n')
            {
                line[i] = '\0';
                break;
            }
        }
        pid = fork();
        if (pid == 0)
        {
            char *argv[2];
            argv[0] = line;
            argv[1] = NULL;
	    if (execve(line,argv,environ) == -1)
                perror("./shell");
            exit(1);
        }
        else
            wait(NULL);
    }
}
