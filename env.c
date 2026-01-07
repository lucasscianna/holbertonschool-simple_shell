#include "shell.h"
#include <string.h>
/**
 * print_env2 - Prints the current environment variables
 */
void print_env2(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
