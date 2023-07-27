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

#endif /* SHELL_H */
