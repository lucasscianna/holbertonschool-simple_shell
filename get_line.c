#include "shell.h"

/**
 * get_line - read a line from stdin using getline
 * Return: allocated line without trailing newline, or NULL on EOF
 */
char *get_line(void)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t r;

	r = getline(&line, &n, stdin);
	if (r == -1)
	{
		free(line);
		return (NULL);
	}
	if (r > 0 && line[r - 1] == '\n')
		line[r - 1] = '\0';
	return (line);
}
