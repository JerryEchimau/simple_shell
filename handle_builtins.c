#include "shell.h"

/**
 * handle_builtin - Handles built-in shell commands.
 * @args: An array of strings containing the command and its arguments.
 *        args[0] is the command.
 *
 * Return: 0 if the command is a built-in, 1 otherwise.
 */
int handle_builtin(char **args, char *line)
{
	if (strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, line));
	else if (strcmp(args[0], "env") == 0)
		return (builtin_env(args));
	else if (strcmp(args[0], "setenv") == 0)
		return (builtin_setenv(args));
	else if (strcmp(args[0], "unsetenv") == 0)
		return (builtin_unsetenv(args));

	/* Add more built-in commands here as you implement them */

	return (1); /* Not a built-in command  */
}
