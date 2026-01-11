#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - Un shell simple capable de gérer les espaces avant/après la commande.
 *
 * Return: Toujours 0 en cas de succès.
 */

int main(void)
{
	char *ligne = NULL;
	size_t longueur = 0;
	pid_t pid;
	int status;
	int inside, start, end;

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

		for (inside = 0; ligne[inside]; inside++)
		{
			if (ligne[inside] == '\n')
			{
				ligne[inside] = '\0';
				break;
			}
		}

		start = 0;
		while (ligne[start] == ' ')
			start++;

		end = inside - 1;
		while (end >= start && ligne[end] == ' ')
		{
			ligne[end] = '\0';
			end--;
		}

		if (ligne[start] == '\0')
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

			argv[0] = &ligne[start];
			argv[1] = NULL;

			if (execve(argv[0], argv, environ) == -1)
			{
				perror(argv[0]);
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
