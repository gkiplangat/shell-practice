#include "main.h"


/**
 * if_file_exists - checks for file status.
 * @s: pointer to file name.
 * Return: 0 success, else non zero number.
 */
int if_file_exists(char *s)
{
	struct stat st;

	return (stat(s, &st));
}


/**
 * path_builder - Create path to binaries.
 * @tokens: double pointer to tokens.
 * Return: Return - path, else - NULL.
 */
char *path_builder(char **tokens)
{
	char path_one[100] = "/bin/";
	char path_two[100] = "/usr/bin/";

	char *finalpath_one;
	char *finalpath_two;

	finalpath_one = _concat_strings(path_one, tokens[0]);

	if ((if_file_exists(finalpath_one) == 0))
		return (finalpath_one);

	finalpath_two = _concat_strings(path_two, tokens[0]);
	if ((if_file_exists(finalpath_two) == 0))
		return (finalpath_two);

	return (NULL);
}

/**
 * execute2 - executes a file.
 * @tokens: Split string from stdin into tokens.
 * @path: path from path_builder function.
 * @args: program arguments.
 * Return: 0 - on success, else - 1.
 */
int execute2(char **tokens, char *path, char *args)
{
	char *first_err, *second_err, *third_err;
	pid_t child_processId;
	int status;

	child_processId = fork();
	if (child_processId == -1)
	{
		perror("Error: ");
		return (1);
	}

	if (child_processId == 0)
	{
		tokens[0] = path;

		if (execve(tokens[0], tokens, NULL) == -1)
		{
			first_err = _concat_strings(*tokens, ": No such file or directory\n");
			second_err = _concat_strings(args, ":");
			third_err = _concat_strings(second_err, first_err);
			write(STDERR_FILENO, third_err, _string_length(third_err));
			free(tokens);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	wait(&status);
	return (EXIT_SUCCESS);
}
