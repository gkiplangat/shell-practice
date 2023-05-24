#include "main.h"

/**
 * prompt_user - Print a cue message to the user.
 * Return: Void.
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
 * _compare_strings - Compares two strings.
 * @s1: Pointer to First string.
 * @s2: Pointer to Second string.
 * Return: 0 if they are equal, Otherwise - positive value.
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

	signal(SIGINT, handle_ctrlc);
	Status = 0;
	while (Status == 0)
	{
		prompt_user();

		line = user_input();
		if (_compare_strings(line, "\n") == 0)
		{
			tokens = NULL;
			free(line);
			continue;
		}
		tokens = _string_tokens(line);
		if (tokens[0] == NULL)
		{
			free(tokens);
			free(line);
			continue;
		}

		if (_compare_strings(tokens[0], "exit") == 0)
		{
			_exit_shell(tokens, line);
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
