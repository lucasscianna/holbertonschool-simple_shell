#include "shell.h"
/**
 * get_line - reads one line from standard input
 *
 * Return: pointer to allocated string, or NULL on EOF/error
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
