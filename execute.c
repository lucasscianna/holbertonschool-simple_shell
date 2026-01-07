#include "shell.h"

/**
 * get_command_path - get full path of a command
 * @cmd: command name (argv[0])
 *
 * Return: full path if found, NULL otherwise
 */
static char *get_command_path(char *cmd)
{
	char *path;

	if (contains_slash(cmd))
	{
		if (access(cmd, X_OK) != 0)
			return (NULL);
		return (cmd);
	}
	path = find_in_path(cmd);
	return (path);
}

/**
 * run_command - fork and execute a command
 * @argv: arguments array
 * @prog: shell program name
 * @line_num: command counter for error messages
 *
 * Return: exit status of the command
 */
static int run_command(char **argv, char *prog, int line_num)
{
	pid_t pid;
	int status;
	char *path = get_command_path(argv[0]);

	if (!path)
		return (print_not_found(prog, line_num, argv[0]), 127);

	pid = fork();
	if (pid == -1)
	{
		if (!contains_slash(argv[0]))
			free(path);
		return (1);
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

	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}

/**
 * execute_cmd - execute a command
 * @argv: arguments array
 * @prog: shell program name
 * @line_num: command counter
 *
 * Return: exit status of the command
 */
int execute_cmd(char **argv, char *prog, int line_num)
{
	if (!argv || !argv[0])
		return (0);
	return (run_command(argv, prog, line_num));
}
