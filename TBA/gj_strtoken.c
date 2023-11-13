#include "shell.h"

/**
* gj_strtoken - A custom function that tokenizes a string
* it works based on the delimiter of the string to be tokenized.
* @string: string to be tokenized which is the first argument.
* @delim: this represents the delimiter ofthe string in what pattern
* to be splitted.
* Return: tokenized string on success, else NULL.
*/

char *gj_strtoken(char *string, const char *delim);

char *gj_strtoken(char *string, const char *delim)
{
	static char *nxt_tkn;

	char *new_tkn;

	if (string != NULL)
	{
		/*Updates the next value of the string*/
		nxt_tkn = string;
	}

	/*Check for the end of tokens in the string*/
	if (nxt_tkn == NULL || *nxt_tkn == '\0')
	{
		/*End of the string null is returned*/
		return (NULL);
	}

	while (*nxt_tkn != '\0' && strchr(delim, *nxt_tkn) != NULL)
	{
		nxt_tkn++;
	}

	/*check for end of tokens*/

	if (*nxt_tkn == '\0')
	{
		return (NULL);
	}

	new_tkn = next_tkn;

	while (*nxt_tkn != '\0' && strchr(delim, *nxt_tkn) == NULL)
	{
		nxt_token += 1;
	}

	if (*nxt_tkn != '\0')
	{
		*nxt_tkn = '\0';

		nxt_tkn += 1;
	}

	/*All strings has been tokenized completely */
	return (new_tkn);
}
