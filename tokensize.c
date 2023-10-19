#include "shell.h"

/**
 * tokensize - tokensizes a buffer with a delimiter
 * @delimiter: delimiter to tokensize along
 * @buffer: buffer to tokensize
 * Return: pointer to an array of pointers to the tokens
 */

char **tokensize(char *buffer, char *delimiter)
{
	char **tokens = NULL;
	size_t s = 0, mcount = 10;

	if (buffer == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * mcount);
	if (tokens == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((tokens[s] = new_strtok(buffer, delimiter)) != NULL)
	{
		s++;
		if (s == mcount)
		{
			tokens = _realloc(tokens, &mcount);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (tokens);
}
