#include "shell.h"

static int str_len(char *s)
{
	int i = 0;

	while (s && s[i])
		i++;
	return (i);
}

char *find_in_path(char *cmd)
{
	char *path, *full;
	int i = 0, start = 0, cmdlen, dirlen, k;

	if (!cmd)
		return (NULL);

	cmdlen = str_len(cmd);

	path = get_env("PATH");
	if (!path)
		return (NULL);

	while (1)
	{
		if (path[i] == ':' || path[i] == '\0')
		{
			dirlen = i - start;

			full = malloc(dirlen + 1 + cmdlen + 1);
			if (!full)
			{
				free(path);
				return (NULL);
			}

			/* copy dir */
			for (k = 0; k < dirlen; k++)
				full[k] = path[start + k];

			full[dirlen] = '/';

			/* copy cmd */
			for (k = 0; k < cmdlen; k++)
				full[dirlen + 1 + k] = cmd[k];

			full[dirlen + 1 + cmdlen] = '\0';

			if (access(full, X_OK) == 0)
			{
				free(path);
				return (full);
			}
			free(full);

			if (path[i] == '\0')
				break;

			start = i + 1;
		}
		i++;
	}

	free(path);
	return (NULL);
}
