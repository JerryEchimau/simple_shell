#include "shell.h"

/**
 * main - entry point for the shell program
 *
 * Return: 0 on success
 */
int main(void)
{
	shell_t shell;
	char *line;

	shell.environ = environ;

	while (1)
	{
		display_prompt();
		line = read_line();
		if (!line)
		{
			break;
		}

		execute_command_with_logical_operators(line, &shell);

		free(line);
	}
	return (0);
}

/**
 * split_commands - Split the input line into separate commands based on the given delimiter.
 * @line: The input line to split.
 * @delimiter: The delimiter to split the line.
 *
 * Return: An array of pointers to the separate commands.
 */
char **split_commands(char *line, const char *delimiter)
{
	char **commands = NULL;
	char *token;
	size_t command_count = 0;

	token = strtok(line, delimiter);
	while (token != NULL)
	{
		commands = realloc(commands, (command_count + 1) * sizeof(char *));
		if (!commands)
		{
			perror("realloc failed");
			exit(EXIT_FAILURE);
		}
		commands[command_count] = strdup(token);
		if (!commands[command_count])
		{
			perror("strdup failed");
			exit(EXIT_FAILURE);
		}
		command_count++;
		token = strtok(NULL, delimiter);
	}
	commands = realloc(commands, (command_count + 1) * sizeof(char *));
	if (!commands)
	{
		perror("realloc failed");
		exit(EXIT_FAILURE);
	}
	commands[command_count] = NULL;

	return commands;
}

/**
 * execute_command_with_logical_operators - Execute commands with logical operators
 * @line: Entire command line
 * @shell: Pointer to the shell structure
 */
void execute_command_with_logical_operators(char *line, shell_t *shell)
{
	char **split_cmds = split_commands(line, ";");
	size_t i;

	for (i = 0; split_cmds[i] != NULL; i++)
	{
		char *logical_cmd = split_cmds[i];
		char **logical_args = (char **) malloc(sizeof(char *));

		logical_args[0] = logical_cmd;
		logical_args[1] = NULL;

		execute_logical_commands(logical_args, shell);
		free(logical_args);
	}

	free_tokens(split_cmds);
}
