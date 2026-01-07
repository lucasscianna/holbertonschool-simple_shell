#include "shell.h"

/**
 * main - entry point
 * @ac: argc
 * @av: argv
 * Return: 0
 */
int main(int ac, char **av)
{
	char *line = NULL;
	char **argv = NULL;
	int line_num = 0;
	int interactive = 0;

	(void)ac;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, PROMPT, _strlen(PROMPT));

		line = get_line();
		if (line == NULL)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}

		line_num++;

		argv = parse_line(line);
		if (argv == NULL)
		{
			free(line);
			continue;
		}
if (argv[0] && _strcmp(argv[0], "exit") == 0)
{
free_argv(argv);
free(line);
exit(0);
}

execute_cmd(argv, av[0], line_num);

free_argv(argv);
free(line);
}
return (0);
}
