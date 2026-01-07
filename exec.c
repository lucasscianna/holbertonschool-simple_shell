#include "shell.h"

/**
 * execute_command - Exécute une commande via fork et execve
 * @argv: Tableau des arguments (argv[0] est la commande)
 * @prog_name: Nom du programme shell
 * @line: Numéro de ligne pour les erreurs
 *
 * Retour: 0 toujours
 *
 * Description:
 * Fonction wrapper qui appelle execute_cmd.
 */
int execute_command(char **argv, char *prog_name, int line)
{
	return (execute_cmd(argv, prog_name, line));
}

