#include "shell.h"

/**
 * print_not_found - prints error like sh
 * @prog: program name
 * @line_num: command count
 * @cmd: command
 */
void print_not_found(char *prog, int line_num, char *cmd)
{
	write(STDERR_FILENO, prog, _strlen(prog));
	write(STDERR_FILENO, ": ", 2);

	print_int(line_num);

	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);
}
