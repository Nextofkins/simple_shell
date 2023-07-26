#include "shell.h"

#define MAX_COMMAND_LENGTH 100

/**
 * main - Entry point for the simple UNIX command line interpreter.
 * Reads and executes user commands until the user enters Ctrl+D (end of file).
 *
 * Return: Always 0.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		display_prompt();
		read_command(command);
		if (command[0] == '\0')
			continue; /* Empty command, show prompt again */

		execute_command(command);
	}

	return (0);
}

/**
 * display_prompt - Display the shell prompt.
 * The prompt is the characters "$ "
 * to indicate that the shell is ready for input.
 */
void display_prompt(void)
{
	printf("$ ");
}

/**
 * read_command - Read a command entered by the user from the standard input.
 * The command is stored in the provided 'command' buffer.
 *
 * @command: The buffer to store the user's command.
 */
void read_command(char *command)
{
	if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
	{
		/* Handle end of file (Ctrl+D) */
		printf("\n");
		exit(EXIT_SUCCESS);
	}

	/* Remove the newline character at the end */
	size_t command_length = strlen(command);

	if (command_length > 0 && command[command_length - 1] == '\n')
		command[command_length - 1] = '\0';
}

/**
 * execute_command - Execute a command entered by the user.
 * The function forks a new process and uses exec to run the command.
 * The parent process waits for the child to complete before continuing.
 *
 * @command: The command to be executed.
 */
void execute_command(const char *command)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		/* Error forking the process */
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process: execute the command */
		if (execlp(command, command, NULL) == -1)
		{
			/* Error executing the command */
			perror("execlp");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process: wait for the child to complete */
		wait(NULL);
	}
}

