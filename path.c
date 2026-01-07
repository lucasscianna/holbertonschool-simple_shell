#include "shell.h"
/**
 * find_in_path - Cherche un exécutable dans le PATH
 * @cmd: Nom de la commande à trouver
 *
 * Retour: Chemin mallocé vers l'exécutable si trouvé, NULL sinon
 *
 * Description:
 * Parcourt les répertoires listés dans la variable d'environnement PATH
 * pour trouver la commande. Retourne le chemin complet si elle existe.
 */
har *find_in_path(char *cmd)
{
	char *path, *full;
	int i = 0, start = 0, dlen, clen = 0, k;

	if (!cmd)
		return (NULL);
	while (cmd[clen])
		clen++;

	path = get_env("PATH");
	if (!path || path[0] == '\0')
{
	free(path);
	return (NULL);
}
	if (!path)
		return (NULL);
	while (1)
	{
		if (path[i] == ':' || path[i] == '\0')
		{
			dlen = i - start;
			full = malloc(dlen + clen + 2);
			if (!full)
				return (free(path), NULL);
			for (k = 0; k < dlen; k++)
				full[k] = path[start + k];
			full[dlen] = '/';
			for (k = 0; k < clen; k++)
				full[dlen + 1 + k] = cmd[k];
			full[dlen + clen + 1] = '\0';
			if (access(full, X_OK) == 0)
				return (free(path), full);
			free(full);
			if (path[i] == '\0')
				break;
			start = i + 1;
		}
		i++;
	}
	return (free(path), NULL);
}
