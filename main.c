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

	while (1)
	{
		print_prompt();
		chars_read = my_getline(&line, &len, stdin);

		/* my_getline return values */
		if (chars_read == -1) /* error */
		{
			perror("my_getline error");
			exit(EXIT_FAILURE);
		}
		else if (chars_read == 0) /* EOF reached or Ctrl+D pressed */
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		args = parse_input(line);
		status = execute_command(args, line); /* exexcute all commands */

		if (WIFEXITED(status))
			printf("Command exited with status: %d\n", WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			printf("Command terminated by signal: %d\n", WTERMSIG(status));

		/* free memory after command execution */
		line = NULL;
		len = 0;
	}

	return (0);
}

/**
 * print_prompt - prints the prompt to standard out
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

