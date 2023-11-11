#include "shell.h"

/**
 * parse_line - parses command line arguments into tokens
 * @line: the input line to parse
 *
 * Return: An array of tokens or NULL on failure
 */
char **parse_line(char *line)
{
	size_t max_tokens = 10;
	char **tokens = malloc(sizeof(char *) * (max_tokens + 1));
	char *token;
	size_t i = 0;

	if (!tokens)
		return (NULL);

	token = strtok(line, " ");
	while (token)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			free_tokens(tokens);
			return (NULL);
		}
		i++;

		if (i > max_tokens)
		{
			max_tokens *= 2;
			tokens = realloc(tokens, sizeof(char *) * (max_tokens + 1));
			if (!tokens)
			{
				free_tokens(tokens);
				return (NULL);
			}
		}
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL; /* null terminate */
	return (tokens);
}

/**
 * free_tokens - frees memory allcated to tokens
 * @tokens: the array of tokens to free
 */
void free_tokens(char **tokens)
{
	size_t i;

	if (tokens)
	{
		for (i = 0; tokens[i]; i++)
			free(tokens[i]);
		free(tokens);
	}
}
