#include "shell.h"

/**
 * get_command_path - Cherche le chemin complet d'une commande
 * @cmd: Nom de la commande (argv[0])
 *
 * Return: Chemin complet de l'exécutable si trouvé, NULL sinon
 *
 * Description:
 * Vérifie si la commande contient un '/', sinon recherche dans PATH.
 */
static char *get_command_path(char *cmd)
{
	char *path;

	if (contains_slash(cmd))
	{
		if (access(cmd, X_OK) != 0)
			return (NULL);
		return (cmd);
	}

	path = find_in_path(cmd);
	return (path);
}

/**
 * run_command - Fork et exécute une commande
 * @argv: Tableau des arguments de la commande (argv[0] est la commande)
 * @prog: Nom du programme shell (argv[0])
 * @line_num: Numéro de ligne pour les messages d'erreur
 *
 * Description:
 * Utilise fork pour créer un processus fils et
 * execve pour exécuter la commande.
 * Affiche un message d'erreur si la commande n'est pas trouvée.
 */
static void run_command(char **argv, char *prog, int line_num)
{
	pid_t pid;
	int status;
	char *path = get_command_path(argv[0]);

	if (!path)
	{
		print_not_found(prog, line_num, argv[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		if (!contains_slash(argv[0]))
			free(path);
		return;
	}

	if (pid == 0)
	{
		execve(path, argv, environ);
		print_not_found(prog, line_num, argv[0]);
		exit(127);
	}

	wait(&status);

	if (!contains_slash(argv[0]))
		free(path);
}

/**
 * execute_cmd - Exécute une commande via fork/execve
 * @argv: Tableau des arguments (argv[0] est la commande)
 * @prog: Nom du programme shell
 * @line_num: Numéro de ligne pour les messages d'erreur
 *
 * Return: Toujours 0
 *
 * Description:
 * Wrapper autour de run_command pour exécuter une commande.
 */
int execute_cmd(char **argv, char *prog, int line_num)
{
	run_command(argv, prog, line_num);
	return (0);
}
