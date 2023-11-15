/* simple_shell.c */

#include "shell.h"

/**
 * main - entry point for the shell program
 *
 * Description: Initializes the shell environment, handles user input,
 * parses commands, and executes them in a loop until the
 * user exits the shell or encounters an error.
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
			write(STDOUT_FILENO, "\n", 1);
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
