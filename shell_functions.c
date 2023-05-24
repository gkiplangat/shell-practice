#include "main.h"

/**
 * _string_length - return string length.
 * @s: pointer to string.
 * Return: string length.
 */
int _string_length(char *s)
{
	int char_index;

	char_index = 0;
	while (s[char_index] != '\0')
	{
		char_index++;
	}
	return (char_index);
}
/**
 * _concat_strings - join strings.
 * @dest: pointer to destination string.
 * @src: pointer to  source string to.
 * Return: pointer to dest.
 */
char *_concat_strings(char *dest, char *src)
{
	char *dest_address;
	int dest_length;

	dest_address = dest;
	dest_length = _string_length(dest);
	dest_address = dest_address + dest_length;
	while (*src != '\0')
	{
		*dest_address = *src;
		src++;
		dest_address++;
	}
	*dest_address = '\0';

	return (dest);
}

/**
 * _check_space - checks for white space.
 * @s: pointer to string to be check.
 * Return: integer.
 */
unsigned int _check_space(char *s)
{
	int i, count = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i]  == ' ' || s[i] == '\t' || s[i] == '\n')
			count++;
	}
	return (count);
}

/**
 * _string_tokens - splits a string into words.
 * @str: pointer to string to be splited.
 * Return: pointer to array of words.
 */
char **_string_tokens(char *str)
{
	int i = 0;
	const char delim[] = " \t\n";
	int space = _check_space(str);
	char **tokens = malloc(sizeof(char *) * (space + 1));
	char *token;

	if (!tokens)
	{
		free(tokens);
		fprintf(stderr, "sh: allocation error\n");
		exit(1);
	}

	token = strtok(str, delim);

	while (token != NULL)
	{
		tokens[i] = token;
		token = strtok(NULL, delim);
		i++;
	}
	tokens[i] =  NULL;

	return (tokens);
}



/**
 * _print_string - prints a string,and a new line, to stdout.
 * @str: string to be printed.
 */

void _print_string(char *str)
{
	unsigned long i = 0;

	while (str[i] != '\0')
	{
		_write_char(str[i]);
		i++;
	}

	_write_char('\n');
}

/**
 * _write_char - print the character c to stdout.
 * @c: character to be printed.
 * Return: - 1 on success.
 */
int _write_char(char c)
{
	return (write(1, &c, 1));
}


/**
 * custom_atoi - converts string to int.
 * @s: string to be converted.
 * Return: number if success and -1 if string contains non-numbers.
 */
int custom_atoi(char *s)
{
	int i = 0;
	unsigned int number = 0;

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')  
			number = number * 10 + (s[i] - '0');
		if (s[i] > '9' || s[i] < '0')  
			return (-1);
		i++;
	}
	return (number);
}


/**
 * _copy_string - copy in src to dest,
 * @dest: Copy source to this buffer.
 * @src: This is the source to copy.
 * Return: a copy original source.
 */

char *_copy_string(char *dest, char *src)
{
	int i, length;

	for (length = 0; src[length] != '\0'; length++)
		;

	for (i = 0; i <= length; i++)
		dest[i] = src[i];

	return (dest);
}
/**
 * check_for_delim - check if char is equal to delim.
 * @c: character to be check.
 * @delim: " "
 * Return: 0 if no match else 1.
 */

int check_for_delim(char c, const char *delim)
{
	while (delim && *delim)
	{
		if (c == *delim)
		{
			return (1);
		}
		++delim;
	}
	return (0);
}

/**
 * _tokenize_string - split string into array of strings.
 * @src: string to be splited.
 * @delim: " ";
 * Return: each token in array format.
 */

char *_tokenize_string(char *src, const char *delim)
{
	static char *s;
	static unsigned int i;
	char *res = NULL;
	int space = 0;

	if (src)
	{
		s = src;
		for (i = 0; s[i]; i++)
		{
			if (check_for_delim(s[i], delim))
				s[i] = '\0';
		}
	}

	if (s == NULL || *s == '\0')
		return (NULL);
	res = s;
	i = _string_length(s);
	if (s[i] == '\0' && _string_length(s) > 0)
		space = 1;
	s = s + _string_length(s) + space;
	return (res);
}

/**
 *handle_ctrlc - handler for control c.
 *@signum: signal number received.
 *
 *Return: void.
 */
void handle_ctrlc(int signum)
{
	(void)signum;

	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}


/**
 * user_command - stores users commands.
 * @str: buffer to store commands.
 * Return: the number of characters read.
 */
ssize_t user_command(char **str)
{
	ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
	char buff[1024];

	 
	while (t2 == 0 && (i = read(STDIN_FILENO, buff, 1024 - 1)))
	{
		if (i == -1)  
			return (-1);

		buff[i] = '\0';  

		n = 0;  
		while (buff[n] != '\0')
		{
			if (buff[n] == '\n')
				t2 = 1;
			n++;
		}

		 
		if (t == 0)  
		{
			i++;
			*str = malloc(sizeof(char) * i);
			*str = _copy_string(*str, buff);
			size = i;
			t = 1;
		}
		else  
		{
			size += i;
			*str = _concat_strings(*str, buff);
		}
	}
	return (size);
}
/**
 *  _dup_string - duplicates string.
 *  @str: string to be duplicated.
 *  Return: pointer to duplicated string.
 */
char *_duplicate_string(char *str)
{
	char *dup_str;
	int i, length = 0;

	if (str == NULL)
		return (NULL);
	while (str[length])
		length++;
	length++;
	dup_str = malloc(sizeof(char) * length);
	if (dup_str == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		dup_str[i] = str[i];
		i++;
	}
	return (dup_str);
}
