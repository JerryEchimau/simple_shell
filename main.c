#include "shell.h"

/**
 * main - entry point for our custom shell
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL; /* for getline to store line */
	size_t len = 0; /* buffer size for getline */
	ssize_t chars_read; /* to store getline's return value */
	char **args; /* tokenized array of strings */
	int status; /* return value of external commands */
	int shell_loop_status = 0; /* status to be returned by the shell */

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();
		chars_read = my_getline(&line, &len, stdin);

		/* Handle my_getline return values */
		if (chars_read == -1) /* error */
		{
			/* error occured during reading */
			perror("my_getline error");
			shell_loop_status = 1; /* indicate error */
			break;
		}
		else if (chars_read == 0) /* EOF reached or Ctrl+D pressed */
		{
			/* write(STDOUT_FILENO, "\n", 1); */
			exit(2); /* exit the shell loop */
		}

		args = parse_input(line); /* tokenize input */
		status = execute_command(args, line); /* exexcute the command */

		/* Update shell loop status */
		if (status != 0)
			shell_loop_status = status;

		/* free memory after command execution */
		line = NULL; /* reset line to NULL */
		len = 0; /* reset len to 0 */
	}

	return (shell_loop_status);
}

/**
 * print_prompt - prints the prompt to standard out
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

