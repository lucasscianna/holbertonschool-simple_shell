#include "shell.h"

/**
 * execute_cmd - executes argv[0] with args, handles PATH
 * @argv: command + args
 * @prog: program name
 * @line_num: line counter
 * Return: 0 always
 */
int execute_cmd(char **argv, char *prog, int line_num)
{
	pid_t pid;
	int status;
	char *path = NULL;

	if (!argv || !argv[0])
		return (0);

	/* Resolve command path BEFORE fork (0.3 requirement) */
	if (contains_slash(argv[0]))
	{
		if (access(argv[0], X_OK) != 0)
		{
			print_not_found(prog, line_num, argv[0]);
			return (0);
		}
		path = argv[0]; /* points into line buffer */
	}
	else
	{
		path = find_in_path(argv[0]); /* malloced or NULL */
		if (!path)
		{
			print_not_found(prog, line_num, argv[0]);
			return (0);
		}
	}

	pid = fork();
	if (pid == -1)
	{
		if (!contains_slash(argv[0]))
			free(path);
		return (0);
	}

	if (pid == 0)
	{
		execve(path, argv, environ);
		print_not_found(prog, line_num, argv[0]);
		exit(127);
	}

	wait(&status);

	if (!contains_slash(argv[0]))
		free(path);

	return (0);
}
