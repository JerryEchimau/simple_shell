#include "shell.h"

/**
 * execute_command - Executes a command, handling both built-in and
 *                   external commands.
 * @args: An array of strings containing the commands and its
 * arguments. Args[0] is the command
 * @line: The original input line read by my_getline() 
 *
 * Return: 1 if the shell should continue, 0 if it shoul exit
 */
int execute_command(char **args, char *line)
{
	pid_t pid; /* Process ID of the child process */
	int status; /* exit status of the child process */
	char *full_path; /* variable to store full path of command */

	if (args[0] == NULL)
		return (1); /* empty command, return to shell */

	/* Check & execute internal commands */
	if (handle_builtin(args, line) == 0)  /* 0 means it's a built-in */
	{
		free(line);
		free(args);
		return (1);  /* Built-in executed, continue shell */
	}

	/* external commands */
	full_path = find_path(args[0]);
	if (full_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		free(line);
		free(args);
		return (1);
	}

	pid = fork(); /* create/fork a child process */

	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		free(line);
		free(args);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) /* child process */
	{
		/* execute external command */
		if (execve(full_path, args, environ) == -1)
		{
			perror("execve error");
			free(full_path);
			free(line);
			free(args);
			exit(EXIT_FAILURE);
		}
		/* execve does not return on success, we should not reach here */
	}
	else /* Parent process */
	{
		waitpid(pid, &status, 0); /* wait for child process to compltete */
	}

	free(full_path);
	free(line);
	free(args);
	return (status); /* return child's exit status */
}
