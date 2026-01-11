#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

char *analyze_line(char *ligne);
void execute_commande(char *command, char *ligne, char **argv);

#endif
