#ifndef SHELL_H
#define SHELL_H

/* Macros */
#define MAX_TOKENS 100
#define MAX_COMMAND_LENGTH 100
#define BUFFER_SIZE 1024

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
 * struct shell - Structure to represent the shell environment
 * @environ: The environment variables
 * @aliases: The list of aliases
 * Add other members as needed for your shell
 */
typedef struct shell
{
	char **environ;
	int last_exit_status;
} shell_t;

/* builtins */


void builtin_env(shell_t *shell);
void builtin_exit(char **args);
void builtin_setenv(char **args);
void builtin_unsetenv(char **args);
void builtin_alias(char **args);


void builtin_cd(char **args);
char *get_new_dir(char **args);
void handle_change_to_prev_dir(char *old_dir);
void change_dir_and_update_env(char *new_dir, char *old_dir);


/* function prototypes */
void display_prompt(void);

char *read_line(void);
void handle_sigint(int signo);
void setup_signal_handler(void);

char **parse_line(char *line, shell_t *shell);
char *replace_variables(char *str, shell_t *shell);
void free_tokens(char **tokens);

int execute_command(char **args, shell_t *shell);
int is_builtin(const char *command);
void execute_builtin(const char *command, char **args, shell_t *shell);
char *find_command(const char *command, shell_t *shell);
char *find_full_path(const char *dir, const char *command);

void print_error(const char *message);

char *str_concat(const char *s1, const char *s2);
char *gj_strtoken(char *string, const char *delim);
char *str_replace(const char *str, const char *old, const char *new);

char *_getline(void);
ssize_t _read_chars(char *buffer, size_t size);
char *_append_to_line(char *line, size_t *len, char c);

void execute_logical_commands(char **logical_cmds, shell_t *shell);
void execute_and_logical_command(char *logical_cmd, shell_t *shell, int *last_status);
void execute_or_logical_command(char *logical_cmd, shell_t *shell, int *last_status);


/* main function */
int main(void);
char **split_commands(char *line, const char *delimiter);
void execute_command_with_logical_operators(char *line, shell_t *shell);

/* external variables */
extern char **environ;

#endif /* SHELL_H */
