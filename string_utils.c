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
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);
	char *result = malloc(len1 + len2 + 1);

	if (!result) {
		return (NULL);
	}

	strcpy(result, s1);
	strcat(result, s2);

	return (result);
}


/**
 * gj_strtoken - A custom function that tokenizes a string
 * @string: string to be tokenized which is the first argument.
 * @delim: this represents the delimiter ofthe string
 *
 * Return: tokenized string on success, else NULL.
 */

char *gj_strtoken(char *string, const char *delim)
{
	static char *nxt_tkn;

	char *new_tkn;

	if (string != NULL)
		nxt_tkn = string; /*Updates the next value of the string*/

	/*Check for the end of tokens in the string*/
	if (nxt_tkn == NULL || *nxt_tkn == '\0')
		return (NULL); /*End of the string null is returned*/

	while (*nxt_tkn != '\0' && strchr(delim, *nxt_tkn) != NULL)
		nxt_tkn++;

	/*check for end of tokens*/
	if (*nxt_tkn == '\0')
		return (NULL);

	new_tkn = nxt_tkn;

	while (*nxt_tkn != '\0' && strchr(delim, *nxt_tkn) == NULL)
		nxt_tkn += 1;

	if (*nxt_tkn != '\0')
	{
		*nxt_tkn = '\0';
		nxt_tkn += 1;
	}

	/*All strings have been tokenized completely */
	return (new_tkn);
}
