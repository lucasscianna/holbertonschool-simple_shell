#include "shell.h"

void execute_command(char *line, char *prog_name)
{
	pid_t pid;
	char *argv[2];
	int status;

	pid = fork();
	if (pid == 0)
	{
		argv[0] = line;
		argv[1] = NULL;

		execve(line, argv, environ);
		perror(prog_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}
