#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototypes */

void display_prompt(void);
void read_command(char *command);
void execute_command(const char *command);
void execute_command(const char *command);
char *find_command_path(const char *command);
void execute_command_with_path(const char *full_path, const char *command);
void execute_command(const char *command);
void print_command_not_found(const char *command);
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

#endif /* SHELL_H */
