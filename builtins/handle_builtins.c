#include "shell.h"

/**
 * handle_builtin - Handles built-in shell commands.
 * @args: An array of strings containing the command and its arguments.
 *        args[0] is the command.
 *
 * Return: 1 if the command is a built-in, 0 otherwise.
 */
int handle_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		return (builtin_exit(args));
	}
	else if (strcmp(args[0], "env") == 0)
	{
		return (builtin_env(args));
	}

	/* Add more built-in commands here as you implement them */

	return (0); /* Not a built-in command  */
}
