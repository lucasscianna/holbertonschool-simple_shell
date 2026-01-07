#include "shell.h"
#include <string.h>
/**
 * handle_builtin - Gère les commandes internes (built-ins)
 * @argv: Tableau des arguments de la commande
 * @line: Numéro de la ligne pour les messages d'erreur
 *
 * Retour: 1 si une commande interne a été exécutée, 0 sinon
 *
 * Description:
 * Vérifie si la commande tapée est un built-in ('exit' ou 'env').
 * Si oui, l'exécute directement sans fork.
 */
int handle_builtin(char *line)
{
	if (strcmp(line, "exit") == 0)
		exit(0);

	if (strcmp(line, "env") == 0)
	{
		print_env();
		return (1);
	}
	return (0);
}
/**
 * print_env - Affiche toutes les variables d'environnement
 *
 * Description:
 * Parcourt le tableau environ et écrit
 * chaque variable sur la sortie standard.
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
