#include "shell.h"

/**
 * env_output - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int env_output(info_t *info)
{
	print_str_list(info->env);
	return (0);
}

/**
 * retrieve_env - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *retrieve_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;
	/* Iterate through the environment variables */
	while (node)
	{
		/* Check if the current variable matches the given name */
		p = is_prefix(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);/*if the environment variable is not found*/
}

/**
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int set_env(info_t *info)
{
	/*Check if the correct number of arguments is provided*/
	if (info->argc != 3)
	{
		show_input("Incorrect number of arguements\n");
		return (1);
	}
	/* Initialize or modify the environment variable */
	if (init_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unset_env(info_t *info)
{
	int i;
	/* Check if too few arguments are provided */
	if (info->argc == 1)
	{
		show_input("Too few arguements.\n");
		return (1);
	}
	/*loop through provided arg & remove corresponding env*/
	for (i = 1; i <= info->argc; i++)
		del_env(info, info->argv[i]);

	return (0);
}

/**
 * built_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int built_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;
	/*loop through the env var & append them to the linked list*/
	for (i = 0; environ[i]; i++)
		append_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}
