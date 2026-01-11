#include "shell.h"

int main(int argc, char **argv)
{
	char *ligne = NULL, *command;
	size_t longueur = 0;
	pid_t pid;
	int status;
	char *args[2];
	(void)argc;

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
		command = parse_line(ligne);
		if (command == NULL)
			continue;
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		if (pid == 0)
		{
			args[0] = command;
			args[1] = NULL;
			if (execve(command, args, environ) == -1)
			{
				perror(argv[0]);
				free(ligne);
				exit(1);
			}
		}
		else
			wait(&status);
	}
	free(ligne);
	return (0);
}
