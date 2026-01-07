#include "shell.h"

/**
 * main - entry point
 * @ac: argc
 * @av: argv
 * Return: 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (*line == '\0')
			continue;
		if (handle_builtin(line))
			continue;

		execute_command(line, argv[0]);
	}
	free(line);
	return (0);
}
