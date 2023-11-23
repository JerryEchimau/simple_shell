/* execute_helper2.c */

#include "shell.h"

/**
 * wait_for_child_process - Wait for the completion of the child process
 * @child_pid: Process ID of the child process.
 * @status: Pointer to the status variable.
 * @shell: Pointer to the shell structure.
 */
void wait_for_child_process(pid_t child_pid, int *status, shell_t *shell)
{
	waitpid(child_pid, status, 0);
	if (WIFEXITED(*status))
	{
		shell->last_exit_status = WEXITSTATUS(*status);
	}
}

/**
 * handle_command_not_found - Print an error message for a command not found.
 * @command: The command that was not found.
 * Return: 127
 */
int handle_command_not_found(const char *command)
{
	char *error_message = str_concat(command, ": command not found\n");

	print_error(error_message);
	free(error_message);
	return (127);
}
