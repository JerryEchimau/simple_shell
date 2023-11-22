/* execute_command.c */

#include "shell.h"

/**
 * execute_command - Execute the given command using execve.
 * @args: An array of command and arguments.
 * @shell: Pointer to the shell structure
 */
int execute_command(char **args, shell_t *shell)
{
	pid_t child_pid;
	int status;

	if (is_builtin(args[0])) /* Handle built-in commands */
		execute_builtin(args[0], args, shell);
	else
	{
		char *command_path = find_command(args[0], shell);

		if (command_path != NULL)
		{
			child_pid = fork();
			if (child_pid == -1) /* child process fails */
			{
				perror("fork");
				free(command_path);
				return (-1);
			}
			if (child_pid == 0) /* success */
			{
				if (execve(command_path, args, shell->environ) == -1)
				{
					perror("execve");
					free(command_path);
					_exit(126);
				}
			}
			else /* parent process */
			{
				waitpid(child_pid, &status, 0);
				if (WIFEXITED(status))
					shell->last_exit_status = WEXITSTATUS(status);
			}
			free(command_path);
		}
		else
		{/* Command not found */
			char *error_message = str_concat(args[0], ": command not found\n");

			print_error(error_message);
			free(error_message);
		}
	}
	return (0);
}


/**
 * is_builtin - Check if the given command is a built-in command.
 * @command: The command to check.
 * Return: 1 if the command is a built-in, 0 otherwise.
 */
int is_builtin(const char *command)
{
	return (strcmp(command, "env") == 0
			|| strcmp(command, "exit") == 0
			|| strcmp(command, "setenv") == 0
			|| strcmp(command, "unsetenv") == 0
			|| strcmp(command, "cd") == 0
			|| strcmp(command, "alias") == 0);
}

/**
 * execute_builtin - Execute the given built-in command.
 * @command: The built-in command to execute.
 * @args: an array of commands and arguments
 * @shell: Pointer to the shell structure
 */
void execute_builtin(const char *command, char **args, shell_t *shell)
{
	if (strcmp(command, "env") == 0)
		builtin_env(shell);
	else if (strcmp(command, "exit") == 0)
		builtin_exit(args);
	else if (strcmp(command, "setenv") == 0)
		builtin_setenv(args);
	else if (strcmp(command, "unsetenv") == 0)
		builtin_unsetenv(args);
	else if (strcmp(command, "cd") == 0)
		builtin_cd(args);
	else if (strcmp(command, "alias") == 0)
		builtin_alias(args);
}

/**
 * find_command - Find the full path of a command in the PATH environment variable
 * @command: The command to be found
 * @shell: Pointer to the shell
 *
 * Return: The full path of the command if found, otherwise NULL
 */
char *find_command(const char *command, shell_t *shell)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");
	char *full_path = NULL;
	char *command_path = NULL;
	(void)shell;

	if (!path_copy)
	{
		return (NULL);
	}

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, F_OK) == 0)
		{
			command_path = strdup(command);
		}
		free(path_copy);
		return (command_path);
	}

	while (token != NULL)
	{
		full_path = find_full_path(token, command);
		if (full_path != NULL)
		{
			command_path = strdup(full_path);
			free(full_path);
			free(path_copy);
			return command_path;
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * find_full_path - Find the full path of a command in the given directory
 * @dir: The directory to search for the command
 * @command: The command to be found
 *
 * Return: The full path of the command if found, otherwise NULL
 */
char *find_full_path(const char *dir, const char *command)
{
	int size = snprintf(NULL, 0, "%s/%s", dir, command);
	char *full_path = malloc(size + 1);

	if (size < 0)
	{
		return (NULL);
	}

	if (!full_path)
	{
		return (NULL);
	}

	snprintf(full_path, size + 1, "%s/%s", dir, command);

	if (access(full_path, F_OK) == 0)
	{
		return (full_path);
	}
	free(full_path);
	return (NULL);
}
