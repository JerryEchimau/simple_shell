/* error_handling.c */

#include "shell.h"

/**
 * print_error - Print error messages.
 * @message: The error message to print.
 */
void print_error(const char *message)
{
	size_t message_length = strlen(message);
	char *error_message = malloc(message_length + 1);

	if (error_message == NULL)
	{
		perror("malloc");
		return;
	}

	strncpy(error_message, message, message_length);
	error_message[message_length] = '\0'; /* Ensure null-termination */
	write(STDERR_FILENO, error_message, message_length);

	free(error_message);
}
