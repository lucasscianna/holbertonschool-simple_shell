#include "shell.h"
/**
 * main - Point d'entrée de la shell
 * @ac: Nombre d'arguments
 * @av: Tableau des arguments
 *
 * Retour: 0 en cas de succès
 *
 * Description:
 * Boucle principale du shell. Affiche le prompt, lit la ligne de commande,
 * parse la ligne, exécute la commande et gère les built-ins comme 'exit'.
 */
int main(int ac, char **av)
{
	char *line;
	char **argv;
	int n = 0, interactive = isatty(STDIN_FILENO);

	(void)ac;
	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, PROMPT, _strlen(PROMPT));

		line = get_line();
		if (!line)
			return (interactive ? (write(1, "\n", 1), 0) : 0);

		n++;
		argv = parse_line(line);
		if (!argv)
		{
			free(line);
			continue;
		}

		if (argv[0] && _strcmp(argv[0], "exit") == 0)
			return (free_argv(argv), free(line),
				argv[1] ? _atoi(argv[1]) : 0);

		execute_cmd(argv, av[0], n);
		free_argv(argv);
		free(line);
	}
}


