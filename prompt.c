/* prompt.c */

#include "shell.h"

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}
