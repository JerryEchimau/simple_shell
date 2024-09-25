#include "shell.h"

/**
 * builtin_setenv -  Sets an environment variable.
 * @args: An array of strings containing the command and its arguments.
 *        args[0] is "setenv", args[1] is the variable name, and 
 *        args[2] is the value.
 *
 * Return: 0 on success, 1 on failure. 
 */
int builtin_setenv(char **args) 
{
	if (args[1] == NULL || args[2] == NULL) 
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1); /* Failure */
	}

	if (setenv(args[1], args[2], 1) != 0) /* Overwrite existing variable */
	{ 
		perror("setenv");
		return (1); /* Failure */
	}

	return (0); /* Successa*/
}
