/* read_line.c */

#include "shell.h"

/**
 * read_line - Read a line of input from the user.
 *
 * Return: A pointer to the user's input or NULL on EOF.
 */
char *read_line(void)
{
	char *line;

	setup_signal_handler();

	line = _getline();

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
	write(STDOUT_FILENO, "\n", 1);
	display_prompt();
}

/**
 * setup_signal_handler - Set up the signal handler for Ctrl+C (SIGINT)
 */
void setup_signal_handler(void)
{
	signal(SIGINT, handle_sigint);
}
