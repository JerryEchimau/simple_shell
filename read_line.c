/* read_line */

#include "shell.h"

/**
 * read_line - read a line of input from the user
 *
 * Return: a pointer to the user's input or NULL on EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_chars;

	setup_signal_handler();

	read_chars = getline(&line, &len, stdin);

	if (read_chars == -1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		free(line);
		return (NULL);
	}

	if (read_chars > 0 && line[read_chars - 1] == '\n')
		line[read_chars - 1] = '\0';

	signal(SIGINT, SIG_DFL); /* reset signal handler */

	return (line);
}

/**
 * handle_sigint - Signal handler for Ctrl+C (SIGINT)
 * @signo: Signal number
 */
void handle_sigint(int signo)
{
	(void)signo;  /* Suppress unused parameter warning */
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}

/**
 * setup_signal_handler - Set up the signal handler for Ctrl+C (SIGINT)
 */
void setup_signal_handler(void)
{
	signal(SIGINT, handle_sigint);
}
