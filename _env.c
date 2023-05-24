#include "shell.h"

/**
 * _setenv - updates environment variable.
 * @var_name:variable name.
 * @var_value:variable value.
 * Return:0 on success else -1.
 */
int _setenv(char *var_name, char *var_value)
{
	int i = 0;
	size_t name_length;
	char *new_variable;

	name_length = _string_length(var_name);
	i = 0;
	
	while (environ[i])
	{
		if (strncmp(environ[i], var_name, name_length) == 0)
		{
			new_variable = var_build(var_name, var_value);
			
			environ[i] = NULL;
			environ[i] = _duplicate_string(new_variable);
			free(environ[i]);
			environ[i] = _duplicate_string(new_variable);
			free(new_variable);
			return (0);
		}
		i++;
	}
	
	new_variable = var_build(var_name, var_value);
	free(environ[i]);
	environ[i] = _duplicate_string(new_variable);
	i++;
	environ[i] = NULL;
	new_variable = NULL;

	return (0);
}
/**
 * var_build - Builds an environment
 * @var_name: variable name.
 * @var_value: variable value.
 * Return:full environment variable.
 */
char *var_build(char *var_name, char *var_value)
{
	char *new_variable;
	size_t variable_length;

	variable_length = _string_length(var_name) + _string_length(var_value) + 2;
	new_variable = malloc(sizeof(char) * variable_length);
	if (new_variable == NULL)
	{
		perror("Error: Insufficient memory\n");
		return (NULL);
	}
	memset(new_variable, 0, variable_length);
	 
	new_variable = _concat_strings(new_variable, var_name);
	new_variable = _concat_strings(new_variable, "=");
	new_variable = _concat_strings(new_variable, var_value);

	return (new_variable);
}
/**
 * _unsetenv - removes an environment variable.
 * @var_name: variable name.
 * Return: 0 success else -1.
 */
int _unsetenv(char *var_name)
{
	int i = 0;
	char **env_tmp;
	size_t name_length;

	name_length = _string_length(var_name);
	while (environ[i])
	{
		if (strncmp(environ[i], var_name, name_length) == 0)
		{
			env_tmp = environ;
			free(env_tmp[0]);
			do {
				env_tmp[0] = env_tmp[1];
				env_tmp++;
			} while (*env_tmp);
		}
		i++;
	}
	return (0);
}
