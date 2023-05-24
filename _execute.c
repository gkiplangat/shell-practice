#include "main.h"

/**
 * _execute - Executes a file.
 * @tokens: split string into tokens from stdin.
 * @args: the program arguments.
 * Return: 0 success. otherwise - 1.
 */
int _execute(char **tokens, char *args)
{
	char *first_err, *second_err, *thirrd_err;
	pid_t child_processId;
	int status;
	char *path;
	/* check if the first token is a built in or not */
	if (_isBuiltIn(*tokens) == 0)
	{
		status = _executeBuiltIn(tokens);
		return (status);
	}
	 
	path = path_builder(tokens);
	if (path != NULL)
	{
		status = execute2(tokens, path, args);
		return (status);
	}
	/* if path was entered e.g /bin/ls */
	child_processId = fork();
	if (child_processId == -1)
	{
		perror("Error: ");
		return (1);
	}
	if (child_processId == 0)
	{

		if (execve(tokens[0], tokens, NULL) == -1)
		{
			first_err = _concat_strings(*tokens, ": No such file or directory\n");
			second_err = _concat_strings(args, ":");
			thirrd_err = _concat_strings(second_err, first_err);
			write(STDERR_FILENO, thirrd_err, _string_length(thirrd_err));
			free(tokens);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	wait(&status);
	return (0);
}

