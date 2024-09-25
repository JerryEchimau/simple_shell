#include "shell.h"

/**
 * construct_path - Constructs the full path to an executable.
 * @directory: The directory path.
 * @command: The command name.
 *
 * Return: The dynamically allocated full path string, or NULL on error.
 */
char *construct_path(const char *directory, const char *command)
{
	/* +2 for '/' and '\0' */
	size_t path_len = strlen(directory) + strlen(command) + 2;
	char *full_path = malloc(path_len);

	if (full_path == NULL)
	{
		perror("full path malloc failed");
		return (NULL);
	}

	/* write the combined path into fullpath */
	snprintf(full_path, path_len, "%s/%s", directory, command);
	return (full_path);
}

/**
 * is_executable - Checks if a file exists and is executable.
 * @file_path: The full path to the file.
 *
 * Return: 1 if the file is executable, 0 otherwise.
 */
int is_executable(const char *file_path)
{
	struct stat buffer;

	if (stat(file_path, &buffer) == 0 && (buffer.st_mode & S_IXUSR))
		return (1);

	return (0);
}

/**
 * search_path - Searches for the command in the PATH environment variable.
 * @command: The command to find.
 *
 * Return: The full path of the command if found, otherwise NULL.
 */
char *search_path(char *command)
{
	char *path = getenv("PATH"); /* get the path variable */
	char *path_copy, *path_token, *full_path;

	if (path != NULL)
	{
		path_copy = strdup(path); /* Create a copy of PATH to tokenize */
		if (path_copy == NULL)
		{
			perror("strdup failed");
			return (NULL);
		}

		path_token = my_strtok(path_copy, ":");  /* Tokenize the PATH */
		while (path_token != NULL)
		{
			full_path = construct_path(path_token, command);  /* Construct full path */
			if (full_path == NULL)
			{
				free(path_copy);
				return (NULL);
			}

			if (is_executable(full_path))  /* Check if it's executable */
			{
				free(path_copy);
				return (full_path); /* Found it! */
			}

			free(full_path);
			path_token = my_strtok(NULL, ":"); /* Get the next directory */
		}

		free(path_copy); /* Free the PATH copy */
	}

	return (NULL); /* Command not found */
}

/**
 * find_path - Finds the full path of a command.
 * @command: The command to find.
 *
 * Return: The full path of the command if found, otherwise NULL.
 */
char *find_path(char *command)
{
	/* 1. Handle direct paths first */
	if (command[0] == '/')
	{
		if (is_executable(command))
			return strdup(command); /* Return a copy of the direct path */
		else
			return (NULL); /* Direct path but not executable */
	}

	/* 2. Search PATH if not a direct path */
	return (search_path(command));
}
