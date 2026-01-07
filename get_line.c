#include "shell.h"
/**
 * get_line - Lit une ligne depuis l'entrée standard
 *
 * Retour: Pointeur vers la chaîne allouée contenant la ligne,
 *         ou NULL en cas de fin de fichier (Ctrl+D) ou erreur.
 *
 * Description: Utilise getline() pour
 * récupérer la ligne tapée par l'utilisateur.
 */
char *get_line(void)
{
	char *buf = malloc(BUFSIZE);
	char c;
	ssize_t rd;
	int i = 0, size = BUFSIZE;

	if (!buf)
		return (NULL);

	while ((rd = read(STDIN_FILENO, &c, 1)) > 0)
	{
		if (c == '\n')
			break;

		buf[i++] = c;
		if (i >= size - 1)
		{
			char *tmp = realloc(buf, size * 2);

			if (!tmp)
				return (free(buf), NULL);
			buf = tmp;
			size *= 2;
		}
	}
	if (rd <= 0)
		return (free(buf), NULL);

	buf[i] = '\0';
	return (buf);
}
