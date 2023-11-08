#include "shell.h"

/**
* gj_getenv - The custom getenv function that would be used
* to get the current enviroment of my shell.
* @env_nam: this represents the enviroment to be gotten as an argument.
* Return: on sucess it returns the environment, else NULL.
*/

char *gj_getenv(char *env_nam)
{
	char **env;

	size_t fp = 0;

	char *ent_env;

	if (env_nam == NULL) /*No valid name was found*/
	{
		return (NULL);
	}

	/* Loop through the enviroment variables*/

	for (env = environ; *env != NULL; env++)
	{
		ent_env = *env;

		fp = _strlen(env_nam);

		if (gj_strncmp(ent_env, env_nam, fp) == 0 && ent_env[ln] == '=')
		{
			return (&ent_env[fp + 1]);
		}
	}

	return (NULL);
}
