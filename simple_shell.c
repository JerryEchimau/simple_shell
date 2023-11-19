/* simple_shell.c */

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
	char **split_cmds;

	shell.environ = environ;

	while (1)
	{
		display_prompt();
		line = read_line();
		if (line == NULL) /* EOF (Ctrl + D) */
		{
			break;
		}

		split_cmds = split_commands(line);
		execute_commands(split_cmds, &shell);

		free(line);
	}
	return (0);
}


/**
 * split_commands - Split the input line into separate commands based on the ";" delimiter.
 * @line: The input line to split.
 *
 * Return: An array of pointers to the separate commands.
 */
char **split_commands(char *line)
{
	char **commands = NULL;
	char *token;
	size_t command_count = 0;

	token = gj_strtoken(line, ";");
	while (token != NULL)
	{
		commands = realloc(commands, (command_count + 1) * sizeof(char *));
		if (commands == NULL)
		{
			perror("realloc failed");
			exit(EXIT_FAILURE);
		}
		commands[command_count] = strdup(token);
		command_count++;
		token = gj_strtoken(NULL, ";");
	}
	commands = realloc(commands, (command_count + 1) * sizeof(char *));
	if (commands == NULL)
	{
		perror("realloc failed");
		exit(EXIT_FAILURE);
	}
	commands[command_count] = NULL;

	return (commands);
}

/**
 * execute_commands - Execute the separate commands.
 * @commands: An array of pointers to the separate commands.
 * @shell: Pointer to the shell structure.
 */
void execute_commands(char **commands, shell_t *shell)
{
	size_t i;

	for (i = 0; commands[i] != NULL; i++)
	{
		char **args = parse_line(commands[i]);
		if (args && args[0])
		{
			execute_command(args, shell);
		}
		free_tokens(args);
	}
	free(commands);
}
