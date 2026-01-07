#include "shell.h"
/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: exit status
 */
int main(int ac, char **av)
{
	char *line;
	char **argv;
	int n = 0, interactive = isatty(STDIN_FILENO);
	int last_status = 0, code;

	(void)ac;
	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, PROMPT, _strlen(PROMPT));

		line = get_line();
		if (!line)
			return (interactive ? (write(1, "\n", 1), last_status) : last_status);

		n++;
		argv = parse_line(line);
		if (!argv)
		{
			free(line);
			continue;
		}

		if (argv[0] && _strcmp(argv[0], "exit") == 0)
		{
			code = (argv[1] ? _atoi(argv[1]) : last_status);
			free_argv(argv);
			free(line);
			return (code);
		}

		last_status = execute_cmd(argv, av[0], n);
		free_argv(argv);
		free(line);
	}
}
