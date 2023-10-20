#include "shell.h"
/**
 * _puts_2 - prints str to standard error
 * @str: str parameter
 * Return: void
 */
void _puts_2(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		exit(1);
	}
}


/**
 * print_error - error messages to standard error
 * @vars: pointer to struct of variables
 * @msg: message to print out
 * Return: void
 */
void print_error(vars_t *vars, char *msg)
{
	char *count;

	_puts_2(vars->argv[0]);
	_puts_2(": ");
	count = _uitoa(vars->count);
	_puts_2(count);
	free(count);
	_puts_2(": ");
	_puts_2(vars->av[0]);
	if (msg)
	{
		_puts_2(msg);
	}
	else
		perror("");
}


/**
 * _uitoa - converts an unsigned int to a string
 * @count: unsigned int to convert
 * Return: pointer to the converted string
 */
char *_uitoa(unsigned int count)
{
	char *numstr;
	unsigned int tmp, digits;

	tmp = count;
	for (digits = 0; tmp != 0; digits++)
		tmp /= 10;
	numstr = malloc(sizeof(char) * (digits + 1));
	if (numstr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	numstr[digits] = '\0';
	for (--digits; count; --digits)
	{
		numstr[digits] = (count % 10) + '0';
		count /= 10;
	}
	return (numstr);
}
