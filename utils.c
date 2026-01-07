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
#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: 0 if equal, <0 or >0 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;

	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
