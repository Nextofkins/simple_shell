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

#endif /* SHELL_H */
