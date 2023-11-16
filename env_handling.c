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
