/* error_handling */

#include "shell.h"

/**
 * print_error - Print error messages.
 * @message: The error message to print.
 */
void print_error(char *message)
{
	write(STDERR_FILENO, message, strlen(message));
}
