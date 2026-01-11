#include "shell.h"

/**
 * parse_line - Cleans the input line and extracts the command.
 * @line: The raw string read from stdin.
 *
 * Return: Pointer to the start of the command, or NULL if empty.
 */

char *parse_line(char *line)
{
	int i = 0;
	char *command;

	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
	command = line;
	while (*command == ' ' || *command == '\t')
		command++;
	if (*command == '\0')
		return (NULL);
	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == ' ' || command[i] == '\t')
		{
			command[i] = '\0';
			break;
		}
	}
	return (command);
}
