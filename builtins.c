#include "shell.h"
#include <string.h>
/**
 * handle_builtin - Handles built-in commands (like exit or env)
 * @argv: Array of arguments from the command line
 *
 * Return: 1 if a built-in command was executed, 0 otherwise
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
