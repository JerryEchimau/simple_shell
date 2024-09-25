#include "shell.h"

static int read_and_append(FILE *stream, char *line, size_t *i, size_t line_size);
static ssize_t refill_buffer(FILE *stream, char *buffer, size_t buf_size);
static char *resize_line(char *line, size_t *line_size);


/**
 * my_getline - reads input from stdin to a line buffer for processing
 * @lineptr: pointer to line (for control)
 * @n: size of line buffer
 * @stream: Input stream (stdin in our case)
 *
 * Return: Number of chars read (excluding \0),
 * 0 on EOF, -1 on error
 */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t i = 0; /* track position at line */
	char *line = NULL; /* line to be filled */
	size_t line_size = 128; /* initial size of line */
	int result; /* stores the return value of read_and_append */

	line = malloc(line_size); /* allocate memory for line */
	if (line == NULL)
		return (-1);

	while (1) /* loop to read into line */
	{
		result = read_and_append(stream, line, &i, line_size);
		if (result == 1)
			break; /* newline encountered */
		else if (result == 0) /* EOF */
		{
			if (i == 0) /* at the beginning of line */
			{
				free(line);
				return (0);
			}
			break;
		}
		else if (result == 2) /* No error */
			continue;
		else if (result < 0) /* read() error */
		{
			if (i == 0)
			{
				free(line);
				return (-1);
			}
			break;
		}
	}
	line[i] = '\0'; /* null-terminate line */
	*lineptr = line;
	*n = line_size;
	return (i);
}

/**
 * read_and_append - Reads a single character, resizes line if needed,
 * and appends the character read to line buffer
 *
 * @stream: The input stream to read from
 * @line: pointer to the line to be filled (line buffer)
 * @i: pointer to the current index in the line buffer (from my_getline)
 * @line_size: current size of the line buffer
 *
 * Return: 0 - EOF, 1 - \n, 2 normal char, -1 error
 */
static int read_and_append(FILE *stream, char *line, size_t *i, size_t line_size)
{
	static char buffer[1024]; /* buffer to store chunks from stream */
	static size_t buf_pos = 0; /* current position in the buffer */
	static ssize_t chars_read = 0; /* stores chars read into this buffer */
	char c; /* variable that temporarily holds chat at buf_pos to append */

	/* refill buffer (first read or if needed) */
	if (buf_pos >= (size_t)chars_read)
	{
		chars_read = refill_buffer(stream, buffer, sizeof(buffer));

		/* return values of refill_buffer/read() */
		if (chars_read < 0) /* error */
		{
			perror("refill_buffer error");
			return (-1);
		}
		else if (chars_read == 0) /* EOF */
			return (0);

		buf_pos = 0; /* reset at every new read */
	}
	/* read from buffer & append to line */
	c = buffer[buf_pos++];

	/* check if the line buffer is full and reallocates */
	if (*i + 1 >= line_size)
	{
		line = resize_line(line, &line_size);
		if (line == NULL)
		{
			perror("resize_line error");
			free(line);
			return (-1);
		}
	}

	line[(*i)++] = c; /* transfer c to line */
	return ((c == '\n') ? 1 : 2); /* return 1 if \n and 2 if normal */
}


/**
 * refill_buffer - Refils the static buffer with characters from stream
 * @stream: the input stream to read from
 * @buffer: pointer to the buffer to store the chars in
 * @buf_size: size of buffer (size to b e read into the buffer)
 *
 * Return: No of chars read, 0 on EOF, -1 on error
 */
static ssize_t refill_buffer(FILE *stream, char *buffer, size_t buf_size)
{
	return (read(fileno(stream), buffer, buf_size));
}


/**
 * resize_line - doubles the size of line buffer (line)
 * @line: pointer to the line buffer
 * @line_size: pointer to the line_size variable
 *
 * Return: A pointer to the new, resized line buffer
 */
static char *resize_line(char *line, size_t *line_size)
{
	*line_size *= 2; /* multiply by 2 */
	line = realloc(line, *line_size); /* reallocate line using new size */

	if (line == NULL)
		return (NULL);

	return (line); /* return new line location */
}
