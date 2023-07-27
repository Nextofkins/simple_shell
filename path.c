#include "shell.h"

#define MAX_COMMAND_LENGTH 100

/**
 ** find_command_path - Find the full path of the command in the PATH.
 **
 ** function searches for the full path of a command in the PATH directories.
 **
 ** @command: The command name to search for.
 ** Return: The full path or NULL if not found.
 **/

char *find_command_path(const char *command)
{
	char *path = getenv("PATH");

	if (path == NULL)
	{
		printf("PATH environment variable not set.\n");
		return (NULL);
	}

	char *directories = strdup(path);
	char *dir = strtok(directories, ":");
	char full_path[MAX_COMMAND_LENGTH];
	int found = 0;
	char *result = NULL;

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			result = strdup(full_path);
			found = 1;
			break;
		}

		dir = strtok(NULL, ":");
	}

	free(directories);

	if (!found)
	{
		return (NULL); /* Return NULL if the command is not found in PATH */
	}

	return (result);
}

/**
 ** execute_command_with_path - Execute the command with the full path.
 **
 ** function runs the command at the specified
 **full path using execvp in a new process.
 ** @full_path: Full path of the executable command.
 ** @command:   Command name with its arguments.
 **/

void execute_command_with_path(const char *full_path, const char *command)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process: execute the command with arguments */
		if (execvp(full_path, (char *const *)&command) == -1)
		{
			perror("execvp");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process: wait for the child to complete */
		wait(NULL);
	}
}

/**
 ** print_command_not_found - Print error message for command not found.
 **
 ** function prints an error message for the specified
 **command not found in the PATH.
 ** @command: Command name not found.
 **/

void print_command_not_found(const char *command)
{
	printf("Command not found: %s\n", command);
}

/**
 ** execute_command - Execute a user-entered command with PATH handling.
 **
 ** function executes the user-entered command,finds the command's full path
 ** using find_command_path and executes it with execute_command_with_path.
 ** Prints an error message if the command is not found in PATH.
 **
 ** @command: User-entered command.
 **/

void execute_command(const char *command)
{
	char *full_path = find_command_path(command);

	if (full_path == NULL)
	{
		print_command_not_found(command);
		return;
	}

	execute_command_with_path(full_path, command);

	free(full_path);
}

/**
 ** main - Entry point of the simple UNIX command line interpreter.
 **
 ** function reads and executes user-entered commands using execute_command.
 **
 ** Return: 0 on successful execution.
 **/

int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		printf("$ ");
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

		execute_command(command);
	}

	return (0);
}

