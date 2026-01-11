#include "shell.h"

/**
 * main - Entry point for the simple shell.
 * @argc: Argument count (unused).
 * @argv: Argument vector.
 *
 * Return: Always 0 on success.
 */

int main(int argc, char **argv)
{
	char *line = NULL, *command;
	size_t length = 0;
	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "#cisfun$ ", 9);

		if (getline(&line, &length, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			free(line);
			exit(0);
		}

		command = parse_line(line);
		if (command != NULL)
			execute_cmd(command, line, argv);
	}
	free(line);
	return (0);
}
