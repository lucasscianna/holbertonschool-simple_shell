#include "shell.h"

int execute_cmd(char **argv, char *prog, int line_num)
{
	pid_t pid;
	int status;
	char *path;

	if (!argv || !argv[0])
		return (0);

	path = argv[0];
	if (!contains_slash(argv[0]))
	{
		path = find_in_path(argv[0]);
		if (!path)
			return (print_not_found(prog, line_num, argv[0]), 0);
	}
	else if (access(argv[0], X_OK) != 0)
		return (print_not_found(prog, line_num, argv[0]), 0);

	pid = fork();
	if (pid == -1)
		return (!contains_slash(argv[0]) ? (free(path), 0) : 0);

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

