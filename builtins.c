#include "shell.h"
#include <string.h>
/**
 * handle_builtin - handle built-in commands
 * @line: input line
 *
 * Return: 1 if builtin handled, 0 otherwise
 */

int handle_builtin(char *line)
{
	if (strcmp(line, "exit") == 0)
		exit(0);

	if (strcmp(line, "env") == 0)
	{
		print_env();
		return (1);
	}
	return (0);
}
/**
 * print_env - Affiche toutes les variables d'environnement
 *
 * Description:
 * Parcourt le tableau environ et écrit
 * chaque variable sur la sortie standard.
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
