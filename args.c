#include "shell.h"

/**
 * execute_command - Execute a command entered by the user with arguments.
 * The function forks a new process and uses exec to run the command.
 * The parent process waits for the child to complete before continuing.
 *
 * @command: The command to be executed along with its arguments.
 */
void execute_command(const char *command)
{
	char *arguments[MAX_COMMAND_LENGTH];
	char *token;
	int arg_index = 0;

	/* Tokenize the command line into command and arguments */
	token = strtok((char *)command, " ");
	while (token != NULL)
	{
		arguments[arg_index] = token;
		token = strtok(NULL, " ");
		arg_index++;
	}

	/* Ensure the last argument is NULL for the exec function */
	arguments[arg_index] = NULL;

	pid_t pid = fork();

	if (pid < 0)
	{
		/* Error forking the process */
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process: execute the command with arguments */
		if (execvp(arguments[0], arguments) == -1)
		{
			/* Error executing the command */
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

