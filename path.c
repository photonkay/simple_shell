#include "shell.h"

/**
 * check_for_path - checks if command is in the PATH
 * @vars: variables
 * Return: void
 */

void check_for_path(vars_t *vars)
{
	char *path, *path_dup = NULL, *check = NULL;
	unsigned int s = 0, r = 0;
	char **path_tokens;
	struct stat buf;

	if (check_for_dir(vars->av[0]))
		r = execute_cwd(vars);
	else
	{
		path = find_path(vars->env);
		if (path != NULL)
		{
			path_dup = _strdup(path + 5);
			path_tokens = tokensize(path_dup, ":");
			for (s = 0; path_tokens && path_tokens[s]; s++, free(check))
			{
				check = _strcat(path_tokens[s], vars->av[0]);
				if (stat(check, &buf) == 0)
				{
					r = path_execute(check, vars);
					free(check);
					break;
				}
			}
			free(path_dup);
			if (path_tokens == NULL)
			{
				vars->status = 127;
				new_exit(vars);
			}
		}
		if (path == NULL || path_tokens[s] == NULL)
		{
			print_error(vars, ": not found\n");
			vars->status = 127;
		}
		free(path_tokens);
	}
	if (r == 1)
		new_exit(vars);
}


/**
 * find_path - finds the PATH variable
 * @env: array of environment variables
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */

char *find_path(char **env)
{
	char *path = "PATH=";
	unsigned int y, z;

	for (y = 0; env[y] != NULL; y++)
	{
		for (z = 0; z < 5; z++)
			if (path[z] != env[y][z])
				break;
		if (z == 5)
			break;
	}
	return (env[y]);
}


/**
 * check_for_dir - checks if the command is a part of a path
 * @str: parameter
 * Return: 1 on success, 0 on failure
 */
int check_for_dir(char *str)
{
	unsigned int x;

	for (x = 0; str[x]; x++)
	{
		if (str[x] == '/')
			return (1);
	}
	return (0);
}


/**
 * path_execute - executes command in the path
 * @command: parameter
 * @vars: pointer to struct of variables
 * Return: 0 on success, 1 on failure
 */

int path_execute(char *command, vars_t *vars)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
			print_error(vars, NULL);
		if (child_pid == 0)
		{
			if (execve(command, vars->av, vars->env) == -1)
				print_error(vars, NULL);
		}
		else
		{
			wait(&vars->status);
			if (WIFEXITED(vars->status))
				vars->status = WEXITSTATUS(vars->status);
			else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
				vars->status = 130;
			return (0);
		}
		vars->status = 127;
		return (1);
	}
	else
	{
		print_error(vars, ": Permission denied\n");
		vars->status = 126;
	}
	return (0);
}


/**
 * execute_cwd - executes the command in the current working directory
 * @vars: pointer to struct of variables
 * Return: 0 on success, 1 on failure
 */

int execute_cwd(vars_t *vars)
{
	pid_t child_pid;
	struct stat buf;

	if (stat(vars->av[0], &buf) == 0)
	{
		if (access(vars->av[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				print_error(vars, NULL);
			if (child_pid == 0)
			{
				if (execve(vars->av[0], vars->av, vars->env) == -1)
					print_error(vars, NULL);
			}
			else
			{
				wait(&vars->status);
				if (WIFEXITED(vars->status))
					vars->status = WEXITSTATUS(vars->status);
				else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
					vars->status = 130;
				return (0);
			}
			vars->status = 127;
			return (1);
		}
		else
		{
			print_error(vars, ": Permission denied\n");
			vars->status = 126;
		}
		return (0);
	}
	print_error(vars, ": not found\n");
	vars->status = 127;
	return (0);
}
