#include "shell.h"

/**
 * contains_slash - Checks if a string contains a '/'
 * @s: String to check
 *
 * Return: 1 if '/' is present, 0 otherwise
 */
int contains_slash(char *s)
{
	int i = 0;

	if (!s)
	return (0);
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

/**
 * get_env - Returns a malloced copy of the value of an environment variable
 * @name: Name of the environment
 *variable (e.g., "PATH")
 * Return: Pointer to malloced string with value
 *, or NULL if not found/memory error
 */
char *get_env(char *name)
{
	int i = 0, j = 0, len = 0;

	char *env, *val, *copy;

	if (!name)
	return (NULL);

	while (name[len])
		len++;

	while (environ[i])
	{
		env = environ[i];
		if (_strncmp(env, name, len) == 0 && env[len] == '=')
		{
			val = env + len + 1;

			while (val[j])
				j++;

			copy = malloc(j + 1);

			if (!copy)
			return (NULL);

			for (j = 0; val[j]; j++)
				copy[j] = val[j];
			copy[j] = '\0';
			return (copy);
		}
		i++;
	}
	return (NULL);
}
/**
 * print_int - print an integer to standard error
 * @n: number to print
 */
void print_int(int n)
{
	char c;

	if (n < 0)
	{
		c = '-';
		write(STDERR_FILENO, &c, 1);
		n = -n;
	}

	if (n / 10)
		print_int(n / 10);

	c = (n % 10) + '0';
	write(STDERR_FILENO, &c, 1);
}
