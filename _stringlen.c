#include "shell.h"

/**
* _stringlen - A function that returns the length of a string.
* @string: string array to be counted.
* Return: Length of the string.
*/

int _stringlen(char *string)
{
	int length_counter = 0;

	while (*string != '\0')
	{
		length_counter += 1;

		string += 1;
	}

	return (length_counter);
}
