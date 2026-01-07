#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

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

#endif
