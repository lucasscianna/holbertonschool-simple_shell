#include "shell.h"
#include <string.h>

/**
 * count_tokens - counts tokens in line
 * @line: input
 * Return: token count
 */
static int count_tokens(char *line)
{
	int count = 0;
	char *copy, *tok;

	copy = strdup(line);
	if (!copy)
		return (0);

	tok = strtok(copy, DELIMS);
	while (tok)
	{
		count++;
		tok = strtok(NULL, DELIMS);
	}
	free(copy);
	return (count);
}

/**
 * parse_line - split line into argv[]
 * @line: input (will be modified)
 * Return: argv array or NULL
 */
char **parse_line(char *line)
{
	int nt, i = 0;
	char **argv;
	char *tok;

	nt = count_tokens(line);
	if (nt == 0)
		return (NULL);

	argv = malloc(sizeof(char *) * (nt + 1));
	if (!argv)
		return (NULL);

	tok = strtok(line, DELIMS);
	while (tok)
	{
		argv[i++] = tok;
		tok = strtok(NULL, DELIMS);
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * free_argv - free argv array (not tokens)
 * @argv: argv
 */
void free_argv(char **argv)
{
	free(argv);
}
