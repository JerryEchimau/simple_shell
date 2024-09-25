#include "shell.h"

/**
 * builtin_unsetenv - Unsets (removes) an environment variable.
 * @args: An array of strings containing the command and its arguments.
 *        args[0] is "unsetenv", args[1] is the variable name.
 *
 * Return: 0 on success, 1 on failure.
 */
int builtin_unsetenv(char **args)
{
	if (args[1] == NULL) 
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1); /* Failure */
	}

	if (unsetenv(args[1]) != 0) 
	{
		perror("unsetenv"); 
		return (1); /* Failure */
	}

	return (0); /* Success */
}
