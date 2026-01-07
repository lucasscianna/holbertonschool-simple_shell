#include "shell.h"

/**
 * _strlen - Returns the length of a string
 * @s: Pointer to the string
 *
 * Return: Length of the string, 0 if NULL
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (s[i])
	{
		i++;
	}
	return (i);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: 0 if strings are equal, difference of first unmatched char otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	if (!s1 || !s2)
	return (1);
	while (s1[i] && s1[i] == s2[i])
		i++;

	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * _strncmp - Compares the first n characters of two strings
 * @s1: First string
 * @s2: Second string
 * @n: Number of characters to compare
 *
 * Return: 0 if first n characters are equal, difference
 * of first unmatched char otherwise
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
 * is_exit - Checks if a string is "exit"
 * @s: String to check
 *
 * Return: 1 if string is "exit", 0 otherwise
 */
int is_exit(char *s)
{
	if (!s)
	return (0);
	return (s[0] == 'e' && s[1] == 'x' && s[2] == 'i' &&
			s[3] == 't' && s[4] == '\0');
}

/**
 * _atoi - Converts a numeric string to an integer
 * @s: String containing a number
 *
 * Return: Integer value of the string, 0 if string is NULL
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
