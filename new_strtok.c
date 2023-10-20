#include "shell.h"

/**
 * check_match - checks if a character matches any in a string
 * @c: character to check
 * @str: string to check
 * Return: 1 if match, 0 if not
 */

unsigned int check_match(char c, const char *str)
{
	unsigned int s;

	for (s = 0; str[s] != '\0'; s++)
	{
		if (c == str[s])
			return (1);
	}
	return (0);
}


/**
 * new_strtok - custom strtok
 * @str: str parameter
 * @delim: delimiter to tokenize against
 * Return: pointer to the next token or NULL
 */

char *new_strtok(char *str, const char *delim)
{
	static char *token_start;
	static char *next_token;
	unsigned int w;

	if (str != NULL)
		next_token = str;
	token_start = next_token;
	if (token_start == NULL)
		return (NULL);
	for (w = 0; next_token[w] != '\0'; w++)
	{
		if (check_match(next_token[w], delim) == 0)
			break;
	}
	if (next_token[w] == '\0' || next_token[w] == '#')
	{
		next_token = NULL;
		return (NULL);
	}
	token_start = next_token + w;
	next_token = token_start;
	for (w = 0; next_token[w] != '\0'; w++)
	{
		if (check_match(next_token[w], delim) == 1)
			break;
	}
	if (next_token[w] == '\0')
		next_token = NULL;
	else
	{
		next_token[w] = '\0';
		next_token = next_token + w + 1;
		if (*next_token == '\0')
			next_token = NULL;
	}
	return (token_start);
}
