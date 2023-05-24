#include "shell.h"

/**
 * prompt_user - rint a cue message to the user.
 * Return: void.
 */
void prompt_user(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
	}
}

/**
 * user_input - Get user input from the command line as a string.
 * Return: Pointer to the line(string).
 */

char *user_input(void)
{
	char *lineptr =  NULL;
	size_t len = 0;
	ssize_t chars = 0;

	/* get user inputs */
	chars = getline(&lineptr, &len, stdin);

	
	if (chars == EOF)
	{
		free(lineptr);
		exit(0);
	}
	if (lineptr == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(lineptr);
		exit(-1);
	}

	return (lineptr);
}
/**
 * _compare_strings - compares two strings.
 * @s1: first string.
 * @s2: second string.
 * Return: 0 if equal, otherwise positive value.
 */

int _compare_strings(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

/**
 * main - point.
 * @argc: argument count.
 * @argv: argument vector.
 * Return: 0 on success else 1.
 */

int main(int argc, char *argv[])
{
	char *linep;
	int status;
	char **tokens;

	(void)argc;

	signal(SIGINT, handle_ctrlc);
	status = 0;
	while (status == 0)
	{
		prompt_user();

		linep = user_input();
		if (_compare_strings(linep, "\n") == 0)
		{
			tokens = NULL;
			free(linep);
			continue;
		}
		tokens = _string_tokens(linep);
		if (tokens[0] == NULL)
		{
			/*free memory*/
			free(tokens);
			free(linep);
			continue;
		}

		if (_compare_strings(tokens[0], "exit") == 0)
		{
			_exit_shell(tokens, linep);
		}
		else
		{
			status =  _execute(tokens, argv[0]);
		}
		/*free memory*/
		free(linep);
		free(tokens);
	}
	return (status);
}
