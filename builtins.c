/* builtins.c */

#include "shell.h"

/**
 * builtin_env - Execute the env built-in command.
 * @shell: Pointer to the shell structure
 */
void builtin_env(shell_t *shell)
{
	size_t i;

	if (shell == NULL || shell->environ == NULL)
	{
		fprintf(stderr, "Error: Invalid shell or environment\n");
		return;
	}

	for (i = 0; shell->environ[i] != NULL; i++)
	{
		if (write(STDOUT_FILENO, shell->environ[i], strlen(shell->environ[i])) == -1)
		{
			perror("write");
			return;
		}
		if (write(STDOUT_FILENO, "\n", 1) == -1)
		{
			perror("write");
		}
	}
}

/**
 * builtin_exit - Execute the exit built-in command.
 * @args: an array of commands and arguments
 */
void builtin_exit(char **args)
{
	if (args[1] != NULL)
	{
		int status = atoi(args[1]);
		exit(status);
	}
	else
	{
		exit(0);
	}
}

/**
 * builtin_setenv - Execute the setenv built-in command.
 * @args: an array of commands and arguments
 */
void builtin_setenv(char **args)
{
	if (args[1] != NULL && args[2] != NULL)
	{
		if (setenv(args[1], args[2], 1) != 0)
		{
			perror("setenv");
		}
	}
	else
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
	}
}

/**
 * builtin_unsetenv - Execute the unsetenv built-in command.
 * @args: an array of commands and arguments
 */
void builtin_unsetenv(char **args)
{
	if (args[1] != NULL)
	{
		if (unsetenv(args[1]) != 0)
		{
			perror("unsetenv");
		}
	}
	else
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	}
}
