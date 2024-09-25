#include "shell.h"

/**
 * my_strtok - tokenizes a string into smaller strings according to a delim
 * @str: string to tokenize. Fir first token, pass the actual string.
 * For subsequent calls, pass NULL.
 * @delim: the delimiter strimng (that separate the tokens)
 *
 * Return: A pointer to the next token in the string,
 * NULL if no more tokens are found
 */
char *my_strtok(char *str, const char *delim)
{
	static char *last_pos; /* to track the last token position */
	char *start; /* pointer to the beginning of the next token */
	char *end; /* pointer to the end of the token */

	/* continue from last position, if str is NULL */
	if (!str)
		str = last_pos;

	if (!str)
		return (NULL); /* No more tokens */

	/* skip leading delimiters */
	start = str + strspn(str, delim);

	if (*start == '\0')
		return (NULL); /* string only contains delims */

	/* find end of token */
	end = start + strcspn(start, delim);

	if (*end != '\0')
	{
		*end = '\0'; /* replace the delimiter with a null terminator */
		last_pos = end + 1; /* update the last pos for the next call */
	}
	else
		last_pos = NULL; /* no more tokens */

	return (start); /*return beginning of the token */
}
