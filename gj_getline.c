/* gj_getline.c */

#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * _getline - Read a line of input from the user.
 *
 * Return: A pointer to the user's input or NULL on EOF.
 */
char *_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_index = 0;
	static ssize_t read_chars = 0;

	char *line = NULL;
	size_t line_index = 0;

	while (1)
	{
		if (buffer_index >= (size_t)read_chars)
		{
			buffer_index = 0;
			read_chars = _read_chars(buffer, BUFFER_SIZE);
			if (read_chars <= 0)
			{
				free(line);
				return (NULL);
			}
		}

		if (buffer[buffer_index] == '\n' || buffer[buffer_index] == '\0')
		{
			buffer_index++;
			break;
		}

		line = _append_to_line(line, &line_index, buffer[buffer_index]);
		buffer_index++;
	}

	return (line);
}


/**
 * _read_chars - Read characters into the buffer.
 * @buffer: The buffer to read characters into.
 * @size: The size of the buffer.
 *
 * Return: The number of characters read, or -1 on error.
 */
ssize_t _read_chars(char *buffer, size_t size)
{
	ssize_t read_chars;

	read_chars = read(STDIN_FILENO, buffer, size);
	if (read_chars == -1)
	{
		perror("read");
	}

	return read_chars;
}

/**
 * _append_to_line - Append a character to the line.
 * @line: The current line.
 * @index: The index where the character should be appended.
 * @c: The character to append.
 *
 * Return: A pointer to the updated line.
 */
char *_append_to_line(char *line, size_t *index, char c)
{
	char *new_line;
	size_t new_size;

	if (*index == 0)
	{
		new_line = malloc(2);
	}
	else
	{
		new_size = *index + 2;
		new_line = realloc(line, new_size);
	}

	if (!new_line)
	{
		perror("malloc/realloc");
		free(line);
		exit(EXIT_FAILURE);
	}

	new_line[*index] = c;
	new_line[*index + 1] = '\0';
	(*index)++;

	return new_line;
}
