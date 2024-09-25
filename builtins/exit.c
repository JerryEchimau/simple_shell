#include "shell.h"

/**
 * builtin_exit - Exits the shell.
 * @args: An array of strings containing the command and its arguments.
 *        args[0] is "exit".
 *
 * Return: 0 to exit the shell, 1 to continue.
 */
int builtin_exit(char **args, char *line)
{
	int exit_status = 0; /* Default exit status */

	if (args[1] != NULL) /* Check if an exit status is provided */
	{
		exit_status = atoi(args[1]); /* Convert argument to integer */
	}

	free(line);
	free(args);
	exit(exit_status); /* Exit the shell with the given status */
}
