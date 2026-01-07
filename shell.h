#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define PROMPT "($) "
#define DELIMS " \t\r\n"
#define BUFSIZE 1024

extern char **environ;

char *get_line(void);

char **parse_line(char *line);
void free_argv(char **argv);

int execute_cmd(char **argv, char *prog, int line_num);

void print_not_found(char *prog, int line_num, char *cmd);

int _strlen(char *s);
void print_int(int n);

int _strcmp(char *s1, char *s2);
int is_exit(char *s);
int _atoi(char *s);


char *get_env(char *name);
char *find_in_path(char *cmd);
int _strncmp(char *s1, char *s2, int n);
int contains_slash(char *s);
char *get_env(char *name);
char *find_in_path(char *cmd);
int contains_slash(char *s);
void print_prompt(void);

void print_prompt(void);
int handle_builtin(char *line);
void print_env(void);
void print_env2(void);
#endif
