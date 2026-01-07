#include "shell.h"

/**
 * _strlen - length of string
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

	if (n / 10)
		print_int(n / 10);

	c = (n % 10) + '0';
	write(STDERR_FILENO, &c, 1);
}
