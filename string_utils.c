/* string_utils.c */

#include "shell.h"

/**
 * str_concat - Concatenate two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: A newly allocated concatenated string or NULL on failure.
 */
char *str_concat(const char *s1, const char *s2)
{
	char *result;
	size_t len1, len2, i, j;

	len1 = strlen(s1);
	len2 = strlen(s2);
	result = malloc(len1 + len2 + 1);

	if (!result)
		return (NULL);

	for (i = 0; i < len1; i++)
		result[i] = s1[i];
	for (j = 0; j < len2; j++)
		result[i + j] = s2[j];

	result[i + j] = '\0';

	return (result);
}
