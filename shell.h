/* shell.h */

#ifndef SHELL_H
#define SHELL_H


/* libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/* environment variables */

/**
 * struct shell - Structure representing a shell environment
 * @environ: Array of strings containing the environment variables
 *
 * Description: This structure encapsulates the environment variables
 *              associated with a shell, providing a convenient way to
 *              manage and access the shell environment.
 */
typedef struct shell
{
	char **environ;
} shell_t;


void builtin_env(shell_t *shell);
void builtin_exit(char **args);
void builtin_setenv(char **args);
void builtin_unsetenv(char **args);

/* function prototypes */
void display_prompt(void);

char *read_line(void);
ssize_t _read_chars(char *buffer, size_t size);
char *_append_to_line(char *line, size_t *len, char c);
char *_getline(void);
void handle_sigint(int signo);
void setup_signal_handler(void);

char **parse_line(char *line);
void free_tokens(char **tokens);

void execute_command(char **args, shell_t *shell);
int is_builtin(const char *command);
void execute_builtin(const char *command, char **args, shell_t *shell);
char *find_command(const char *command, shell_t *shell);

void print_error(char *message);

char *str_concat(const char *s1, const char *s2);
char *gj_strtoken(char *string, const char *delim);

/* external variables */
extern char **environ;

#endif /* SHELL_H */
