#include "shell.h"

/**
<<<<<<< HEAD
 * get_line - Lit une ligne depuis l'entrée standard
 *
 * Retour: Pointeur vers la chaîne allouée contenant la ligne,
 *         ou NULL en cas de fin de fichier (Ctrl+D) ou erreur.
 *
 * Description: Utilise getline() pour
 * récupérer la ligne tapée par l'utilisateur.
=======
 * get_line - read a line from stdin using getline
 * Return: allocated line without trailing newline, or NULL on EOF
>>>>>>> 4b1da92 (correction realloc pour le shell 0.3)
 */
char *get_line(void)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t r;

	r = getline(&line, &n, stdin);
	if (r == -1)
	{
		free(line);
		return (NULL);
	}
	if (r > 0 && line[r - 1] == '\n')
		line[r - 1] = '\0';
	return (line);
}
