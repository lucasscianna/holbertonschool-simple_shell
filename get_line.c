#include "shell.h"

/**
 * get_line - reads a line from stdin using read()
 * Return: allocated string, or NULL on EOF/error
 */
char *get_line(void)
{
	int i = 0, size = BUFSIZE;
	ssize_t rd;
	char c;
	char *buf;

	buf = malloc(sizeof(char) * size);
	if (!buf)
		return (NULL);

	while (1)
	{
		rd = read(STDIN_FILENO, &c, 1);
		if (rd == 0)
		{
			free(buf);
			return (NULL); /* EOF */
		}
		if (rd == -1)
		{
			free(buf);
			return (NULL);
		}
		if (c == '\n')
			break;

		buf[i++] = c;

		if (i >= size - 1)
		{
			char *newbuf = realloc(buf, size * 2);

			if (!newbuf)
			{
				free(buf);
				return (NULL);
			}
			buf = newbuf;
			size *= 2;
		}
	}
	buf[i] = '\0';
	return (buf);
}
