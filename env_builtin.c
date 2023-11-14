/* env_builtin.c */

#include "shell.h"

/**
 * env_builtin - Implement the `env` built-in command
 * @shell: environment variable
 */
void env_builtin(shell_t *shell)
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
			return;
		}
	}
}
