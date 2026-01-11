#include "shell.h"

char *parse_line(char *ligne)
{
	int i = 0;
	char *command;

	while (ligne[i])
	{
		if (ligne[i] == '\n')
			ligne[i] = '\0';
		i++;
	}
	command = ligne;
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
