#include "main.h"

/**
 * read_line - reads the input from string.
 *
 * @i_eof: return value of the getline function
 * Return: input string
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t buff = 60;

	*i_eof = getline(&input, &buff, stdin);

	return (input);
}
