/* simple_shell.c */

#include "shell.h"

/**
 * main - entry point for the shell program
 *
 * Return: 0 on success
 */
int main(void)
{
	shell_t shell;
	char *line;
	char **args;

	if (putenv("TERM=xterm-256color") != 0)
	{
		perror("putenv");
		return (EXIT_FAILURE);
	}

	shell.environ = environ;

	while (1)
	{
		display_prompt();
		line = read_line();
		if (line == NULL) /* EOF (Ctrl + D) */
		{
			free(line);
			break;
		}

		args = parse_line(line);
		if (args[0] != NULL)
		{
			execute_command(args, &shell);
		}
		free(line);
		free_tokens(args);
	}
	return (0);
}
