/* prompt.c */

#include "shell.h"

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * main - Entry point for the shell program
 *
 * Return: Always 0
 */
int main(void)
{
	while (1)
	{
		display_prompt();
		if (/* condition to exit the shell */)
		{
			break;
		}
	}
	return (0);
}
