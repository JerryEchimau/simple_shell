/* simple_shell.c */

#include "shell.h"

/**
 * main - entry point for the shell program
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 if a file was provided but could not be opened
 */
int main(int argc, char *argv[])
{
	shell_t shell = {0};
	char *line;
	FILE *fp = stdin;

	shell.environ = environ;

	if (argc > 1)
	{
		fp = fopen(argv[1], "r");
		if (!fp)
		{
			perror("fopen");
			return (1);
		}
	}

	while (1)
	{
		if (fp == stdin)
			display_prompt();

		if (fp == stdin)
			line = read_line();
		else
			line = read_line_from_file(fp);

		if (!line)
			break;

		execute_command_with_logical_operators(line, &shell);
		free(line);
	}

	if (fp != stdin)
		fclose(fp);

	return (0);
}

/**
 * read_line_from_file - Read a line of input from a file.
 * @fp: file pointer
 *
 * Return: A pointer to the line read, or NULL on EOF or error.
 */
char *read_line_from_file(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;

	if (getline(&line, &len, fp) == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

/**
 * split_commands - Split the input into separate commands based on delimiter.
 * @line: The input line to split.
 * @delimiter: The delimiter to split the line.
 *
 * Return: An array of pointers to the separate commands.
 */
char **split_commands(char *line, const char *delimiter)
{
	char **commands = NULL, *token, **tmp;
	size_t command_count = 0, capacity = 10, i, j;

	commands = malloc(capacity * sizeof(char *));
	if (!commands)
	{
		perror("malloc failed");
		return (NULL);
	}
	token = gj_strtoken(line, delimiter);
	while (token != NULL)
	{
		if (command_count >= capacity)
		{
			tmp = realloc(commands, capacity * sizeof(char *));
			capacity *= 2;
			if (!tmp)
			{
				perror("realloc failed");
				for (i = 0; i < command_count; i++)
					free(commands[i]);
				free(commands);
				return (NULL);
			}
			commands = tmp;
		}
		commands[command_count] = strdup(token);
		if (!commands[command_count])
		{
			perror("strdup failed");
			for (j = 0; j < command_count; j++)
				free(commands[j]);
			free(commands);
			return (NULL);
		}
		command_count++;
		token = gj_strtoken(NULL, delimiter);
	}
	commands[command_count] = NULL;
	return (commands);
}


/**
 * execute_command_with_logical_operators - Execute commands logical operators
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
		char **logical_args = (char **)malloc(2 * sizeof(char *));

		logical_args[0] = logical_cmd;
		logical_args[1] = NULL;

		execute_logical_commands(logical_args, shell);
		free(logical_args);
	}

	free_tokens(split_cmds);
}
