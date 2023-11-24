/* parse_line.c */

#include "shell.h"

/**
 * parse_line - parses command line arguments into tokens
 * @line: the input line to parse
 * @shell: Pointer to the shell structure
 *
 * Return: An array of tokens or NULL on failure
 */
char **parse_line(char *line, shell_t *shell)
{
	size_t max_tokens = 10, i = 0;
	char **tokens = malloc(sizeof(char *) * (max_tokens + 1));
	char *token, *comment_start = strchr(line, '#');

	if (!tokens)
		return (NULL);

	if (comment_start) /* Ignore everything after # */
		*comment_start = '\0';

	line = replace_variables(line, shell);
	token = gj_strtoken(line, " ");
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
			char **temp;

			max_tokens *= 2;
			temp = realloc(tokens, sizeof(char *) * (max_tokens + 1));
			if (!temp)
			{
				free_tokens(tokens);
				return (NULL);
			}
			tokens = temp;
		}
		token = gj_strtoken(NULL, " ");
	}
	tokens[i] = NULL; /* null terminate */
	free(line);
	return (tokens);
}


/**
 * replace_variables - Replace the $$, $? and environment variables.
 * @str: The string to replace variables in.
 * @shell: Pointer to the shell structure
 *
 * Return: A newly allocated string with the variables replaced.
 */
char *replace_variables(char *str, shell_t *shell)
{
	char *result, *dollar_dollar, *dollar_question, *start;
	char pid[10], exit_status[4];

	snprintf(pid, sizeof(pid), "%d", getpid());
	snprintf(exit_status, sizeof(exit_status), "%d", shell->last_exit_status);

	dollar_dollar = str_replace(str, "$$", pid);
	dollar_question = str_replace(dollar_dollar, "$?", exit_status);

	start = dollar_question; /* Replace environment variables */
	while ((start = strchr(start, '$')) != NULL)
	{
		char *end = strpbrk(start + 1, " /\\.,;:\"'`~!@#$%^&*()-+=[]{}<>|?");
		char *name, *value;

		if (end == NULL)
			name = strdup(start + 1);
		else
			name = strndup(start + 1, end - start - 1);

		value = getenv(name);
		if (value != NULL)
		{
			char *old = dollar_question;

			dollar_question = str_replace(old, start, value);
			free(old);
		}

		free(name);

		start++;
	}

	result = strdup(dollar_question);

	free(dollar_dollar);
	free(dollar_question);
	return (result);
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
