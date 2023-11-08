#include "shell.h"


/**
* _putchar - Function prints a character to the standard output.
* @chr: character to be printed.
* Return: the printed character to stdout.
*/
int _putchar(char chr)
{
	return (write(1, &chr, 1));
}

/**
* gj_strncmp - A function that compares two strings
* @string1: first string to be comapred.
* @string2: second string to be compared.
* @numb: byte size to be comapared.
* Return: 0 on success.
*/

int gj_strncmp(char *string1, char *string2, int numb)
{
	int compare = 0;

	int n = 0;

	while ((*string1 != '\0' || *string2 != '\0') && n < numb)
	{
		if (*string1 != *string2)
		{
			compare += 1;
		}

		string1 += 1;

		string2 += 1;

		n += 1;
	}

	/*check for valid comparison*/
	if (compare != 0)
	{
		return (-1);
	}

	return (compare);
}
