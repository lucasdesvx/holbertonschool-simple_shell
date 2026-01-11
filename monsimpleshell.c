#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - le simple shell
 *
 * Return: always 0
 */

int main(void)
{
	char *ligne = NULL;
	size_t longueur = 0;
	pid_t pid;
	int status;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "#cisfun$ ", 9);

		if (getline(&ligne, &longueur, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			free(ligne);
			exit(0);
		}

		for (i = 0; ligne[i] != '\0'; i++)
		{
			if (ligne[i] == '\n')
			{
				ligne[i] = '\0';
				break;
			}
		}

		if (ligne[0] == '\0')
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			char *argv[2];

			argv[0] = ligne;
			argv[1] = NULL;

			if (execve(ligne, argv, environ) == -1)
			{
				perror(ligne);
				free(ligne);
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}
	free(ligne);
	return (0);
}
