#include "shell.h"

/**
 * execute_commande - Creates a child process and executes a command
 * @command: pointer
 * @ligne: pointer
 * @argv: double pointer
 *
 * Return: to execute_commande
 */

void execute_commande(char *command, char *ligne, char **argv)
{
	pid_t pid;
	int status;
	char *args[2];

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
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
