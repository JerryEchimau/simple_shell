/* logical_commands.c */

#include "shell.h"

/**
 * execute_logical_commands - Execute logical commands based on the logical AND (&&) and logical OR (||) operators
 * @logical_cmds: Array of logical commands to be executed
 * @shell: Pointer to the shell structure
 */
void execute_logical_commands(char **logical_cmds, shell_t *shell) 
{
	size_t j;
	int last_status = 0; /* Variable to store the status of the last command */

	for (j = 0; logical_cmds[j] != NULL; j++) 
	{
		char **args;

		if (strstr(logical_cmds[j], "&&") != NULL) 
		{
			execute_and_logical_command(logical_cmds[j], shell, &last_status);
		} 
		else if (strstr(logical_cmds[j], "||") != NULL) 
		{
			execute_or_logical_command(logical_cmds[j], shell, &last_status);
		} 
		else 
		{
			args = parse_line(logical_cmds[j]);
			if (args && args[0]) 
			{
				last_status = execute_command(args, shell);
			}
			free_tokens(args);
		}
	}
}

/**
 * execute_and_logical_command - Execute commands separated by logical AND (&&)
 * @logical_cmd: Logical command to be executed
 * @shell: Pointer to the shell structure
 * @last_status: Pointer to the status of the last command
 */
void execute_and_logical_command(char *logical_cmd, shell_t *shell, int *last_status) 
{
	char **split_and_cmds = split_commands(logical_cmd, "&&");
	size_t k = 0;

	while (split_and_cmds[k] != NULL) 
	{
		char **args = parse_line(split_and_cmds[k]);
		if (args && args[0]) 
		{
			*last_status = execute_command(args, shell);
		}
		free_tokens(args);
		if (*last_status != 0) 
		{
			break;  /* If any command fails, break loop */
		}
		k++;
	}

	free_tokens(split_and_cmds);
}

/**
 * execute_or_logical_command - Execute commands separated by logical OR (||)
 * @logical_cmd: Logical command to be executed
 * @shell: Pointer to the shell structure
 * @last_status: Pointer to the status of the last command
 */
void execute_or_logical_command(char *logical_cmd, shell_t *shell, int *last_status) 
{
	char **split_or_cmds = split_commands(logical_cmd, "||");
	size_t k = 0;

	while (split_or_cmds[k] != NULL) 
	{
		char **args = parse_line(split_or_cmds[k]);
		if (args && args[0]) 
		{
			*last_status = execute_command(args, shell);
		}
		free_tokens(args);
		if (*last_status == 0) 
		{
			break;  /* If any command succeeds, break loop */
		}
		k++;
	}

	free_tokens(split_or_cmds);
}
