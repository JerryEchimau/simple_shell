#ifndef SHELL_H
#define SHELL_H

/* libraries */
#include <stdio.h> /* For standard I/O */
#include <stdlib.h> /* For memory allocation, exit, etc. */
#include <unistd.h> /* For fork, execve, etc. */
#include <string.h> /* For string manipulation */
#include <sys/wait.h> /* For wait */
#include <sys/stat.h> /* for file handling */

/* Environment Variables */
extern char **environ; /* declare environ as external */


/* function prototypes */

/* main */
int main(void);
void print_prompt(void);

/* utilities (reading line and handling errors) */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);


/* parsing input string */
char **parse_input(char *line);
char *my_strtok(char *str, const char *delim);

/* Executing commands */
/* external commands */
int execute_command(char **args, char *line);
char *construct_path(const char *directory, const char *command);
int is_executable(const char *file_path);
 char *search_path(char *command);
char *find_path(char *command);

/* builtins */
int handle_builtin(char **args, char *line);
int builtin_exit(char **args, char *line);
int builtin_env(char **args);
int builtin_setenv(char **args);
int builtin_unsetenv(char **args);

#endif /* SHELL_H */
