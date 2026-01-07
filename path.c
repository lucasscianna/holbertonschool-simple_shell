#include "shell.h"
#include <string.h>

/**
 * find_in_path - finds full path of cmd using PATH
 * @cmd: command (ex: "ls")
 * Return: malloced full path or NULL
 */
char *find_in_path(char *cmd)
{
	char *path, *dir, *full;
	int i, dirlen, cmdlen;

	if (!cmd)
		return (NULL);

	cmdlen = 0;
	while (cmd[cmdlen])
		cmdlen++;

	path = get_env("PATH");
	if (!path)
		return (NULL);

	dir = strtok(path, ":");
	while (dir)
	{
		dirlen = 0;
		while (dir[dirlen])
			dirlen++;

		full = malloc(dirlen + 1 + cmdlen + 1);
		if (!full)
		{
			free(path);
			return (NULL);
		}

		for (i = 0; i < dirlen; i++)
			full[i] = dir[i];
		full[dirlen] = '/';
		for (i = 0; i < cmdlen; i++)
			full[dirlen + 1 + i] = cmd[i];
		full[dirlen + 1 + cmdlen] = '\0';

		if (access(full, X_OK) == 0)
		{
			free(path);
			return (full);
		}

		free(full);
		dir = strtok(NULL, ":");
	}

	free(path);
	return (NULL);
}
