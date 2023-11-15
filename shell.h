#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>

#include <stdarg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/* Constants */
#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 1024

/* Structure Definition */
typedef struct shell
{
	char **environ;
	/* Add other members if needed */
} shell_t;

/* Function Prototypes */
void env_builtin(shell_t *shell);
void display_prompt(void);
char *read_line(void);
void handle_sigint(int signo);
void setup_signal_handler(void);
char **parse_line(const char *line, const char *delimiters);
char *_getline(void);
ssize_t _read_chars(char *buffer, size_t size);
char *_append_to_line(char *line, size_t *index, char c);
void free_tokens(char **tokens);
void execute_command(char **args, shell_t *shell);
int is_builtin(const char *command);
void execute_builtin(const char *command, char **args, shell_t *shell);
char *find_command(const char *command, shell_t *shell);
void print_error(char *message);
char *str_concat(const char *s1, const char *s2);

/* External Variables */
extern char **environ;

#endif /* SHELL_H */
