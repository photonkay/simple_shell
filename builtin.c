#include "shell.h"
/**
 * _env - prints the current environment
 * @vars: struct of variables
 * Return: void
 */
void _env(vars_t *vars)
{
	unsigned int w;

	for (w = 0; vars->env[w]; w++)
	{
		_puts(vars->env[w]);
		_puts("\n");
	}
	vars->status = 0;
}


/**
 * check_for_builtin - checks for builtin commands
 * @vars: variables parameter
 * Return: pointer to the function or NULL
 */
void (*check_for_builtin(vars_t *vars))(vars_t *vars)
{
	unsigned int s;

	builtin_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};
	for (s = 0; check[s].f != NULL; s++)
	{
		if (_strcmpr(vars->av[0], check[s].name) == 0)
			break;
	}
	if (check[s].f != NULL)
		check[s].f(vars);
	return (check[s].f);
}


/**
 * new_setenv - create a new environment variable, or edit an existing variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void new_setenv(vars_t *vars)
{
	char **key;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
		add_key(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			print_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}


/**
 * new_unsetenv - remove an environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void new_unsetenv(vars_t *vars)
{
	char **key, **newenv;
	unsigned int x, y;

	if (vars->av[1] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
	{
		print_error(vars, ": No variable to unset");
		return;
	}
	for (x = 0; vars->env[x] != NULL; x++)
		;
	newenv = malloc(sizeof(char *) * x);
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (x = 0; vars->env[x] != *key; x++)
		newenv[x] = vars->env[x];
	for (y = x + 1; vars->env[y] != NULL; y++, x++)
		newenv[x] = vars->env[y];
	newenv[x] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}


/**
 * new_exit - exit program
 * @vars: variables
 * Return: void
 */
void new_exit(vars_t *vars)
{
	int status;

	if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			print_error(vars, ": Illegal number: ");
			_puts_2(vars->av[1]);
			_puts_2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(vars->status);
}
