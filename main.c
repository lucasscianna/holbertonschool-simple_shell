#include "shell.h"

/**
 * display_prompt - Affiche le prompt du shell.
 *
 * Return: Rien.
 */
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}

/**
 * read_command - Lit une ligne de commande depuis l'entree standard.
 *
 * Return: La ligne lue (a liberer avec free), ou NULL si EOF ou erreur.
 */
char *read_command(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t length;

	length = getline(&line, &bufsize, stdin);
	if (length == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

/**
 * main - Point d'entree du programme shell.
 *
 * Return: Toujours 0.
 */
int main(void)
{
	char *input_line;

	display_prompt();

	input_line = read_command();
	if (input_line == NULL)
		return (0);

	printf("%s", input_line);

	free(input_line);

	return (0);
}
