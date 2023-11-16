#include "shell.h"

/**
 * environ_copy - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **environ_copy(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * del_env - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int del_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;
	/* Check if the environment linked list or var is NULL */
	if (!node || !var)
		return (0);
	/*Check if var is a prefix of the current node's str & ends with '='*/
	while (node)
	{
		p = is_prefix(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_at_index(&(info->env), i);
			i = 0;/* Reset the index */
			node = info->env;/*Reset the node pnter to the start*/
			continue;/*Continue to the next iteration*/
		}
		node = node->next;/*Move to the next node in the linked list*/
		i++;/* Increment the index */
	}
	/*Return the value indicating whether the environment was changed*/
	return (info->env_changed);
}

/**
 * init_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int init_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;
	/*Check if var or value is NULL*/
	if (!var || !value)
		return (0);
	/*Allocate memory for the buffer to store the concatenated string*/
	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	/*Allocate memory for the buffer to store the concatenated string*/
	str_copy(buf, var);
	_strconcat(buf, "=");
	_strconcat(buf, value);
	node = info->env;
	/*Traverse the env linked list to check if the var already exists*/
	while (node)
	{
		/* Check var is prefix of current node's str & ends with '='*/
		p = is_prefix(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;/*Move to the next node in the linked list*/
	}
	append_node(&(info->env), buf, 0);
	free(buf);/* Free the allocated buffer */
	info->env_changed = 1;/*Set flag indicate that env was changed*/
	return (0);
}
/**
 * *find_pathtwo - this fuction is able to find path
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @path_env: handle path of directory
 * @command: able to handle any command
 * Return: Always 0
 */
char *find_pathtwo(info_t *info, char *path_env, char *command)
{
	char *path_copy, *token, *full_path;
	size_t command_len, path_len;
	(void)info;

	if (!path_env || !command)
		return (NULL);

	path_copy = dup_str(path_env);
	if (!path_copy)
	{
	perror("dup_str");
	exit(EXIT_FAILURE);
	}
	command_len = str_len(command);
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
	path_len = str_len(token);
	full_path = malloc(path_len + command_len + 2);
	if (!full_path)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	str_copy(full_path, token);
	_strconcat(full_path, "/");
	_strconcat(full_path, command);

	if (access(full_path, X_OK) == 0)
	{
		free(path_copy);/*found the executable,free temporary copy*/
		return (full_path);
	}
	free(full_path);
	token = strtok(NULL, ":");/*Move on to the next directory in PATH*/
	}
	free(path_copy);
	return (NULL);
}
