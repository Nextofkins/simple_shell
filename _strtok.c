#include "shell.h"

#define MAX_COMMAND_LENGTH 100


/**
 ** find_command_path- Find full path of executable command
 ** in PATH directories.
 ** @command: Command name to search for in PATH directories.
 **
 ** Return: Full path as dynamically allocated string,
 ** or NULL if command not found in PATH.
 **/

char *find_command_path(const char *command)
{
	char *path = getenv("PATH");

	if (path == NULL)
	{
		printf("PATH environment variable not set.\n");
		return (NULL);
	}

	char *directory = path;
	size_t command_length = strlen(command);
	char full_path[MAX_COMMAND_LENGTH];
	int found = 0;

	while (*directory != '\0')
	{
		char *end = strchr(directory, ':');

		size_t length = end ? (size_t)(end - directory) : strcspn(directory, ":");

		snprintf(full_path, sizeof(full_path), "%s/%s", directory, command);

		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			break;
		}

		if (end == NULL)
			break;

		directory = end + 1;
	}

	return (found ? strdup(full_path) : NULL);
}

/**
 ** execute_command - Execute user command with PATH handling.
 ** @command: Command entered by the user.
 **
 ** If found, execute the command with execvp. Otherwise, print error message.
 **/

void execute_command(const char *command)
{
	char *full_path = find_command_path(command);

	if (full_path != NULL)
	{
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("fork");
			free(full_path);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execvp(full_path, (char *const *)&command) == -1)
			{
				perror("execvp");
				free(full_path);
				_exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}

		free(full_path);
	}
	else
	{
		printf("Command not found: %s\n", command);
	}
}

/**
 ** main - Entry point of the simple UNIX command line interpreter.
 **
 ** function reads user input, proceses commands, executes them until the user
 ** exits the program. Return: 0 on successful execution,
 ** indicating normal termination.
 ** Return: 0 on successful execution, non-zero value on error.
 **/
int main(void)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t bytes_read;

	while ((bytes_read = getline(&line, &n, stdin)) != -1)
	{
		/* Remove the newline character at the end */
		size_t command_length = strlen(line);

		if (command_length > 0 && line[command_length - 1] == '\n')
			line[command_length - 1] = '\0';

		execute_command(line);
	}

	free(line);

	return (0);
}

