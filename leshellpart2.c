#include "shell.h"

/**
 * execute_cmd - Creates a child process and executes a command.
 * @command: The cleaned command string to execute.
 * @line: The original buffer to be freed on error.
 * @argv: The program's arguments used for error messages.
 */

void execute_cmd(char *command, char *line, char **argv)
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
			free(line);
			exit(1);
		}
	}
	else
		wait(&status);
}
