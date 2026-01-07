#include "shell.h"

/**
 * _strlen - length of a string
 * @s: string
 * Return: length
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (s[i])
		i++;
	return (i);
}

/**
 * print_int - print integer to stderr
 * @n: number
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

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: 0 if equal, otherwise difference
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	if (!s1 || !s2)
		return (1);

	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;

	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * _strncmp - compares n characters of two strings
 * @s1: string 1
 * @s2: string 2
 * @n: number of bytes
 * Return: 0 if equal on n bytes, otherwise difference
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i;

	if (!s1 || !s2 || n <= 0)
		return (1);

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

/**
 * is_exit - checks if token is "exit"
 * @s: token
 * Return: 1 if exit, 0 otherwise
 */
int is_exit(char *s)
{
	if (!s)
		return (0);

	if (s[0] == 'e' && s[1] == 'x' && s[2] == 'i' && s[3] == 't' &&
	    s[4] == '\0')
		return (1);

	return (0);
}

/**
 * _atoi - convert numeric string to int (simple)
 * @s: string
 * Return: int value
 */
int _atoi(char *s)
{
	int i = 0, sign = 1, res = 0;

	if (!s)
		return (0);

	if (s[0] == '-')
	{
		sign = -1;
		i++;
	}

	for (; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			break;
		res = (res * 10) + (s[i] - '0');
	}

	return (res * sign);
}

/**
 * contains_slash - checks if string contains '/'
 * @s: string
 * Return: 1 if contains '/', else 0
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
 * get_env - get env var value (malloced copy)
 * @name: variable name (ex: "PATH")
 * Return: malloced value or NULL
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
