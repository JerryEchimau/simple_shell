#include "shell.h"


/**
 * execute_command - Executes a command, handling both built-in and
 *                   external commands.
 * @args: An array of strings containing the commands and its
 * arguments. Args[0] is the command
 * @line: The original input line read by my_getline()
 *
 * Return: 0 if the command executed successfully, 1 on error or failure
 */
int execute_command(char **args, char *line)
{
        pid_t pid; /* Process ID of the child process */
        int status; /* exit status of the child process */
	char *full_path; /* variable to store full path of command */

        if (args[0] == NULL)
                return (0); /* empty command, return to shell */

        /* Check & execute internal commands */
        if (handle_builtin(args, line) == 0)  /* 0 means it's a built-in */
        {
                free(line);
                free(args);
                return (0);  /* Built-in executed, continue shell */
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

        /* Interpret the status and return 0 for success, 1 for error */
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
                return (0); /* Command executed successfully */
        }
	else
	{
                return (2); /* Command failed (non-zero exit or signal) */
        }
}
