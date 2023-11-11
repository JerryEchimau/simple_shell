#include "shell.h"

/**
 * env_builtin - Implement the `env` built-in command to print the current environment.
 */
void env_builtin(void)
{
	size_t i;
	extern char **environ;  /* Access environment variables */

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
