#include "shell.h"
#include <string.h>
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
