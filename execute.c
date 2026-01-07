#include "shell.h"

int execute_cmd(char **argv, char *prog, int line_num)
{
	pid_t pid;
	int status;
	char *path = NULL;

	if (!argv || !argv[0])
		return (0);

	/* Resolve BEFORE fork */
	if (contains_slash(argv[0]))
	{
		if (access(argv[0], X_OK) != 0)
		{
			print_not_found(prog, line_num, argv[0]);
			return (0);
		}
		path = argv[0];
	}
	else
	{
		path = find_in_path(argv[0]);
		if (!path)
		{
			print_not_found(prog, line_num, argv[0]);
			return (0);
		}
	}

	/* NOW fork only if command exists */
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
