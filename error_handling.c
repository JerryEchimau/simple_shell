#include "shell.h"

/**
 * print_error - Print error messages.
 * @message: The error message to print.
 *
 * Description: This function prints an error message to the standard error
 * output and frees dynamically allocated memory for the message.
 */
void print_error(char *message)
{
	write(STDERR_FILENO, message, strlen(message));

	free(message);
}
