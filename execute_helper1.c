/* execute_helperr1.c */

#include "shell.h"

/**
 * execute_builtin_command - Execute a built-in command.
 * @args: An array of command and arguments.
 * @shell: Pointer to the shell structure.
 */
void execute_builtin_command(char **args, shell_t *shell)
{
	execute_builtin(args[0], args, shell);
}

/**
 * execute_external_command - Execute an external command.
 * @args: An array of command and arguments.
 * @shell: Pointer to the shell structure.
 */
void execute_external_command(char **args, shell_t *shell)
{
	char *command_path = find_command(args[0], shell);

	if (command_path != NULL)
	{
		execute_child_process(args, shell, command_path);
		free(command_path);
	}
	else
	{
		handle_command_not_found(args[0]);
	}
}

/**
 * execute_child_process - Create a child process
 * @args: An array of command and arguments.
 * @shell: Pointer to the shell structure.
 * @command_path: The full path of the external command.
 */
void execute_child_process(char **args, shell_t *shell, char *command_path)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(command_path);
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		execute_child_command(args, shell, command_path);
	}
	else
	{
		wait_for_child_process(child_pid, &status, shell);
	}
}

/**
 * execute_child_command - Execute the command in the child process.
 * @args: An array of command and arguments.
 * @shell: Pointer to the shell structure.
 * @command_path: The full path of the external command.
 */
void execute_child_command(char **args, shell_t *shell, char *command_path)
{
	if (execve(command_path, args, shell->environ) == -1)
	{
		perror("execve");
		free(command_path);
		_exit(EXIT_FAILURE);
	}
}
