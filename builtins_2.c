/* builtins_2.c */

#include "shell.h"

/**
 * get_new_dir - Get the new directory to change to.
 * @args: An array of commands and arguments
 *
 * Return: The new directory path or NULL if invalid
 */
char *get_new_dir(char **args)
{
	if (args[1] == NULL || strcmp(args[1], "~") == 0)
		return (getenv("HOME"));

	else if (strcmp(args[1], "-") == 0)
		return (NULL);

	else
		return (args[1]);
}

/**
 * handle_change_to_prev_dir - Handle changing to the previous directory.
 * @old_dir: The previous directory path
 */
void handle_change_to_prev_dir(char *old_dir)
{
	char *current_dir = getcwd(NULL, 0);

	if (current_dir == NULL)
	{
		perror("getcwd");
		return;
	}

	if (chdir(old_dir) != 0)
		perror("cd");

	else
	{
		fprintf(stderr, "%s\n", old_dir);
		setenv("OLDPWD", current_dir, 1);
	}

	free(current_dir);
}

/**
 * change_dir_and_update_env - Change to specified directory
 * @new_dir: The new directory path
 * @old_dir: The previous directory path
 */
void change_dir_and_update_env(char *new_dir, char *old_dir)
{
	char *new_pwd;

	if (chdir(new_dir) != 0)
	{
		perror("cd");
		return;
	}

	setenv("OLDPWD", old_dir, 1);

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		perror("getcwd");
		return;
	}

	setenv("PWD", new_pwd, 1);

	free(old_dir);
	free(new_pwd);
}

/**
 * builtin_cd - Execute the cd built-in command.
 * @args: An array of commands and arguments
 */
void builtin_cd(char **args)
{
	char *new_dir = get_new_dir(args);

	if (new_dir == NULL)
	{
		handle_change_to_prev_dir(getenv("OLDPWD"));
	}
	else
	{
		char *old_dir = getcwd(NULL, 0);

		if (old_dir == NULL)
		{
			perror("getcwd");
			return;
		}

		change_dir_and_update_env(new_dir, old_dir);
	}
}
