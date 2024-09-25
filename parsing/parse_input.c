#include "shell.h"

/**
 * parse_input - tokenizes the input string into an array of arguments
 * @line: Pointer to the line from getline()
 *
 * Return: A Null-terminated array of strings
 * representing the command and its arguments
 */
char **parse_input(char *line)
{
	int bufsize = 64; /* Initial size of the tokens array */
	int position = 0; /* Current position in the tokens array */
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token; /* pointer to current token */

	/* check for allocation failure */
	if (!tokens)
	{
		perror("tokens malloc");
		exit(EXIT_FAILURE);
	}

	token = my_strtok(line, " \t\n"); /* get the first token */

	/* loop through the tokens to store them in an array */
	while (token)
	{
		tokens[position] = token; /* store token to the array */
		position++; /* move to the next position in array */

		/* check if more space is needed (to store tokens) */
		if (position >= bufsize)
		{
			bufsize += 64; /* double the bufsize */
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("tokens realloc");
				free(tokens);
				exit(EXIT_FAILURE);
			}
		}

		token = my_strtok(NULL, " \t\n"); /* get the next token */
	}

	tokens[position] = NULL; /* NULL terminate the array */
	return (tokens);
}
