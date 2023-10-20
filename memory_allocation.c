#include "shell.h"
/**
 * _realloc - reallocates pointer to double space
 * @ptr: pointer parameter
 * @size: parameter
 * Return: pointer to the new array
 */
char **_realloc(char **ptr, size_t *size)
{
	char **new;
	size_t s;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (s = 0; s < (*size); s++)
	{
		new[s] = ptr[s];
	}
	*size += 10;
	free(ptr);
	return (new);
}
