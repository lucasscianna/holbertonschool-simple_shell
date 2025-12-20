#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Prototypes des fonctions du shell */
void display_prompt(void);
char *read_command(void);

#endif 