#include "shell.h"

/**
 * execute_cmd - executes argv[0] with args
 * @argv: command + args
 * @prog: program name (argv[0] of main)
 * @line_num: line counter
 * Return: 0 always
 */
int execute_cmd(char **argv, char *prog, int line_num)
{
	pid_t pid;
	int status;

	if (!argv || !argv[0])
		return (0);

	pid = fork();
	if (pid == -1)
		return (0);

	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		print_not_found(prog, line_num, argv[0]);
		exit(127);
	}
	wait(&status);
	return (0);
}
