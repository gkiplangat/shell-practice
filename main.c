#include "main.h"

/**
 * prompt - Print prompt.
 * Return: Void.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
	}
}

/**
 * read_line - Gets a typed line from the command line as a string.
 * Return: Pointer to the line(string).
 */

char *read_line(void)
{
	char *line =  NULL;
	size_t len = 0;
	/*int chars = 0;*/
	ssize_t chars = 0;

	/* inbuilt getline */
	chars = getline(&line, &len, stdin);

	/* custom get line */
	/*chars = get_line(&line);*/
	if (chars == EOF)
	{
		free(line);
		exit(0);
	}
	if (line == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(line);
		exit(-1);
	}

	return (line);
}

/**
 * main - Entry to Simple Shell program.
 * @argc: Number of arguments.
 * @argv: Pointer to array of arguments.
 * Return: Always 0 if success else 1.
 */

int main(int argc, char *argv[])
{
	char *line;
	int Status;
	char **tokens;

	(void)argc;

	signal(SIGINT, ctrlc);
	Status = 0;
	while (Status == 0)
	{
		prompt();

		line = read_line();
		if (_strcmp(line, "\n") == 0)
		{
			tokens = NULL;
			free(line);
			continue;
		}
		tokens = _strtotokens(line);
		if (tokens[0] == NULL)
		{
			free(tokens);
			free(line);
			continue;
		}

		if (_strcmp(tokens[0], "exit") == 0)
		{
			_exitSimpleShell(tokens, line);
		}
		else
		{
			Status =  _execute(tokens, argv[0]);
		}
		free(line);
		free(tokens);
	}
	return (Status);
}
