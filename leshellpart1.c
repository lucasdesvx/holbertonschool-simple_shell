#include "shell.h"

/**
 * main - mon shell
 * @argc: variable
 * @argv: double pointer
 *
 * Return: always 0
 */

int main(int argc, char **argv)
{
	char *ligne = NULL, *command;
	size_t longueur = 0;
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

		command = analyze_line(ligne);
		if (command != NULL)
			execute_commande(command, ligne, argv);
	}
	free(ligne);
	return (0);
}
