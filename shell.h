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
typedef struct shell
{
	char **environ;
} shell_t;

extern shell_t shell;

void env_builtin(void);

/* function prototypes */
void display_prompt(void);

char *read_line(void);
void handle_sigint(int signo);
void setup_signal_handler(void);

char **parse_line(char *line);
void free_tokens(char **tokens);

void execute_command(char **args);
int is_builtin(const char *command);
void execute_builtin(const char *command, char **args);
char *find_command(const char *command);

void print_error(char *message);

char *str_concat(const char *s1, const char *s2);

#endif /* SHELL_H */
