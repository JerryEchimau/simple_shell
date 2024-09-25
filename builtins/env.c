#include "shell.h"

/**
 * builtin_env - Prints the current environment.
 * @args: An array of strings (unused).
 *
 * Return: Always returns 0 to continue the shell loop.
 */
int builtin_env(char **args __attribute__((unused)))
{
	int i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}

	return (0);
}
