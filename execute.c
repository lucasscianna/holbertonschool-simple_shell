#include "shell.h"

/**
 * execute_cmd - execute a command with PATH handling
 * @argv: command and arguments
 * @prog: program name
 * @line_num: command count
 *
 * Return: exit status of the command
 */
int execute_cmd(char **argv, char *prog, int line_num)
{
	pid_t pid;
	int st;
	char *path = argv[0];

	if (!argv || !argv[0])
		return (0);

	if (!contains_slash(argv[0]))
	{
		path = find_in_path(argv[0]);
		if (!path)
			return (print_not_found(prog, line_num, argv[0]), 127);
	}
	else if (access(argv[0], X_OK) != 0)
		return (print_not_found(prog, line_num, argv[0]), 127);

	pid = fork();
	if (pid == -1)
		return (!contains_slash(argv[0]) ? (free(path), 1) : 1);

	if (pid == 0)
	{
		execve(path, argv, environ);
		print_not_found(prog, line_num, argv[0]);
		exit(127);
	}

	wait(&st);
	if (!contains_slash(argv[0]))
		free(path);

	return (WIFEXITED(st) ? WEXITSTATUS(st) : 1);
}
