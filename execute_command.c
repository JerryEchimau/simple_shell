/* execute_command.c */

#include "shell.h"

/**
 * execute_command - Execute the given command using execve.
 * @args: An array of command and arguments.
 */
void execute_command(char **args)
{
	pid_t child_pid;
	int status;

	if (is_builtin(args[0]))
	{ /* Handle built-in commands */
		execute_builtin(args[0], args);
	}
	else
	{
		char *command_path = find_command(args[0]);

		if (command_path != NULL)
		{
			child_pid = fork();
			if (child_pid == -1) /* child process fails */
			{
				perror("fork");
				free(command_path);
				return;
			}
			if (child_pid == 0) /* success */
			{
				if (execve(command_path, args, NULL) == -1)
				{
					perror("execve");
					free(command_path);
					_exit(126);
				}
			}
			else /* parent process */
			{
				waitpid(child_pid, &status, 0);
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
}

/**
 * is_builtin - Check if the given command is a built-in command.
 * @command: The command to check.
 * Return: 1 if the command is a built-in, 0 otherwise.
 */
int is_builtin(const char *command)
{
	return (strcmp(command, "env") == 0 || strcmp(command, "exit") == 0);
}

/**
 * execute_builtin - Execute the given built-in command.
 * @command: The built-in command to execute.
 * @args: an array of commands and arguments
 */
void execute_builtin(const char *command, char **args)
{
	if (strcmp(command, "env") == 0)
	{
		env_builtin();
	}
	else if (strcmp(command, "exit") == 0)
	{
		free_tokens(args);
		exit(0);
	}
}

/**
 * find_command - Find the full path of the command using PATH resolution.
 * @command: The command to find.
 * Return: The full path of the command or NULL if not found.
 */
char *find_command(const char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");

	while (token != NULL)
	{
		char *full_path = str_concat(token, "/");
		full_path = str_concat(full_path, command);

		if (access(full_path, F_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":"); /* move to the next command */
	}
	free(path_copy);
	return (NULL);
}
