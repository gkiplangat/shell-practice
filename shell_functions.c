#include "main.h"

/**
 * _string_length - Returns length of a string.
 * @s: Pointer to string.
 * Return: Length of s.
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
 * _concat_strings - Concatenates two strings.
 * @dest: Pointer to string to be conatenated upon.
 * @src: Pointer to string to append to dest.
 * Return: Pointer to dest.
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
 * @s: Pointer to string to check.
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
 * @str: Pointer to string.
 * Return: Pointer to array of words.
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
 * _print_string - prints a string, followed by a new line, to stdout.
 * @str: string to print.
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
 * _write_char - Writes the character c to stdout.
 * @c: The character to print.
 * Return: On success - 1.
 */
int _write_char(char c)
{
	return (write(1, &c, 1));
}


/**
 * custom_atoi - Custom atoi converts string to int.
 * @s: string.
 * Return: Number if success, -1 if string contains non-numbers.
 */
int custom_atoi(char *s)
{
	int i = 0;
	unsigned int number = 0;

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9') /* calculate number */
			number = number * 10 + (s[i] - '0');
		if (s[i] > '9' || s[i] < '0') /* account for non-numberbers */
			return (-1);
		i++;
	}
	return (number);
}


/**
 * _copy_string - Copies the string pointed to by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest.
 * @dest: Copy source to this buffer.
 * @src: This is the source to copy.
 * Return: Copy of original source.
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
 * check_for_delim - Check if char is equal to delim.
 * @c: character.
 * @delim: " "
 * Return: 0 if no match, 1 if matched.
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
 * _tokenize_string - Mimics strtok, which tokenizes a string and turn to array.
 * @src: String from getline.
 * @delim: " ";
 * Return: Individual token in array format.
 */

char *_tokenize_string(char *src, const char *delim)
{
	static char *s;
	static unsigned int i;
	char *result = NULL;
	int is_space = 0;

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
	result = s;
	i = _string_length(s);
	if (s[i] == '\0' && _string_length(s) > 0)
		is_space = 1;
	s = s + _string_length(s) + is_space;
	return (result);
}

/**
 *handle_ctrlc - Control C handler.
 *@signum: The signal number received.
 *
 *Return: Void.
 */
void handle_ctrlc(int signum)
{
	(void)signum;

	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}


/**
 * user_command - Stores into malloced buffer the user's command into shell.
 * @str: Buffer.
 * Return: Number of characters read.
 */
ssize_t user_command(char **str)
{
	ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
	char buff[1024];

	/* read while there's stdin greater than buffsize; -1 to add a '\0' */
	while (t2 == 0 && (i = read(STDIN_FILENO, buff, 1024 - 1)))
	{
		if (i == -1) /* check if read errored */
			return (-1);

		buff[i] = '\0'; /* terminate buff with \0 to use with _concat_strings */

		n = 0; /* last loop if \n is found in the stdin read */
		while (buff[n] != '\0')
		{
			if (buff[n] == '\n')
				t2 = 1;
			n++;
		}

		/* copy what's read to buff into user_command's buffer */
		if (t == 0) /* malloc the first time */
		{
			i++;
			*str = malloc(sizeof(char) * i);
			*str = _copy_string(*str, buff);
			size = i;
			t = 1;
		}
		else /* _realloc via _concat_strings with each loop */
		{
			size += i;
			*str = _concat_strings(*str, buff);
		}
	}
	return (size);
}
/**
 *  _duplicate_string - Duplicates string.
 *  @str: String to duplicate.
 *  Return: Pointer to duplicated string in allocated memory.
 */
char *_duplicate_string(char *str)
{
	char *duplicate_str;
	int i, length = 0;

	if (str == NULL)
		return (NULL);
	while (str[length])
		length++;
	length++; /* add null terminator to lengthgth */
	duplicate_str = malloc(sizeof(char) * length);
	if (duplicate_str == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		duplicate_str[i] = str[i];
		i++;
	}
	return (duplicate_str);
}
