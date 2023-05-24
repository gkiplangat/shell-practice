#include "main.h"

/**
  *_printenv - prints current working enviroment variables
  * Return: void.
  */
void _printenv(void)
{
	int i = 0;

	while (environ[i])
	{
		_print_string(environ[i]);
		i++;
	}
}

/**
 * _isBuiltIn - checks if token is a built in.
 * @str: pointer to string to be check.
 * Return: 0 if true else 1.
 */
int _isBuiltIn(char *str)
{
	/* compare strings they are equal */
	if ((_compare_strings(str, "env")) == 0)
	{
		return (0);
	}
	if ((_compare_strings(str, "exit")) == 0)
		return (0);
	if ((_compare_strings(str, "setenv")) == 0)
		return (0);
	if ((_compare_strings(str, "unsetenv")) == 0)
		return (0);
	return (1);

}

/**
 * _executeBuiltIn - executes a builtin Function.
 * @tokens: double pointer to tokens.
 * Return: 0 on success.
 */
int _executeBuiltIn(char **tokens)
{
	 
	if ((_compare_strings(*tokens, "env")) == 0)
	{
		_printenv();
		return (0);
	}
	if ((_compare_strings(*tokens, "setenv")) == 0)
	{
		 
		if (tokens[1] && tokens[2])
		{
			_setenv(tokens[1], tokens[2]);
			return (0);
		}
		 
		printf("Usage: setenv var_name var_value\n");
		return (0);
	}
	if (_compare_strings(*tokens, "unsetenv") == 0)
	{
		 
		if (tokens[1])
		{
			_unsetenv(tokens[1]);
			return (0);
		}
		 
		printf("Usage: unsetenv VAR_NAME\n");
		return (0);
	}


	return (1);
}
/**
 * _exit_shell - exits the shell and frees memory.
 * @tokens: double pointer to words split from line.
 * @line: pointer to string got.
 * Return: void.
 */
void _exit_shell(char **tokens, char *line)
{
	int status;

	if (tokens[1] != NULL)
	{
		status = atoi(tokens[1]);
		if (status >= 0)
		{
			free(line);
			free(tokens);
			exit(status);
		}
		write(STDERR_FILENO, "Exit: illegal exit status: ", 28);
		write(STDERR_FILENO, tokens[1], 1);
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		free(line);
		free(tokens);
		exit(0);
	}
}
