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

/**
 * str_replace - Replace all occurrences of a substring in a string.
 * @str: The string to replace substrings in.
 * @old: The substring to replace.
 * @new: The substring to replace with.
 *
 * Return: A newly allocated string with the substrings replaced.
 */
char *str_replace(const char *str, const char *old, const char *new)
{
	char *result;
	int i, count = 0;
	int newlen = strlen(new);
	int oldlen = strlen(old);

	for (i = 0; str[i] != '\0'; i++)    {
		if (strstr(&str[i], old) == &str[i]) {
			count++;
			i += oldlen - 1;
		}
	}

	result = (char *)malloc(i + count * (newlen - oldlen) + 1);
	i = 0;
	while (*str) {
		if (strstr(str, old) == str) {
			strcpy(&result[i], new);
			i += newlen;
			str += oldlen;
		} else
			result[i++] = *str++;
	}

	result[i] = '\0';
	return result;
}
