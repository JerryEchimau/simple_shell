/* simple_shell.c */

#include "shell.h"

/**
 * main - entry point for the shell program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line;
	char **args;

	while (1)
	{
		display_prompt();
		line = read_line();
		if (line == NULL) /* EOF (Ctrl + D) */
		{
			break;
		}

		args = parse_line(line);
		if (args[0] != NULL)
		{
			execute_command(args);
		}
		free(line);
		free_tokens(args);
	}
	return (0);
}
