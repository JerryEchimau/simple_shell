#include "shell.h"

/**
* gj_getline - A custom getline function that reads input
* from the terminal and returns the array of characters read.
* It works typically like the traditional getline function.
* Return: this function returns the array of read strings on success.
*/

char *gj_getline(void)
{
	ssize_t getline_re_value;

	char *buffer_pointer = NULL;

	size_t buffer_pointer_length = 0;


	getline_re_value = getline(&buffer_pointer, &buffer_pointer_len, stdin);

	if (getline_re_value == -1)
	{
		/*Check the condition of the end of file*/

		if (feof(stdin))
		{
			_putchar('\n');
			free(buffer_pointer);
			exit(EXIT_SUCCESS);
		}
		else /*This indicates an error cause it's not end of file*/
		{
			free(buffer_pointer);
			perror("Getline Failed");
			exit(EXIT_FAILURE);
		}
	}

	/*Control reads to this point indicate no errors encountered.*/

	return (buffer_pointer);
}
