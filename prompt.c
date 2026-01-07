#include "shell.h"
/**
 * print_prompt - Affiche le prompt du shell
 *
 * Description:
 * Affiche la chaîne définie par PROMPT sur la sortie standard.
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
