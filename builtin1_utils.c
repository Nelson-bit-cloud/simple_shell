#include "shell.h"

/**
 * get_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int get_history(info_t *info)
{
	display_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Delete the alias by locating its index & using the delete_at_index function
 * The prefix_node function is used to find the node associated with the alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;
	/*Find the position of '=' in the string*/
	p = locate_char(str, '=');
	if (!p)
		return (1);/*if '=' not found, indicating an error*/
	c = *p;/*Save the character at the '=' position*/
	*p = 0;/* Replace '=' with 0 terminator to isolate the alias*/
	ret = delete_at_index(&(info->alias),
		node_index(info->alias, prefix_node(info->alias, str, -1)));
	*p = c;/*Restore the original character at '=' position*/
	return (ret);/*Return the result of the delete operation*/
}

/**
 * alias_set - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_set(info_t *info, char *str)
{
	char *p;
	/*Find the position of '=' in the string*/
	p = locate_char(str, '=');
	if (!p)
		return (1);/*if '=' not found, indicating an error*/
	/*If the character after '=' is null, unset the alias*/
	if (!*++p)
		return (unset_alias(info, str));
	/*Unset the existing alias with the same name, append the new alias*/
	unset_alias(info, str);
	return (append_node(&(info->alias), str, 0) == NULL);
}

/**
 * alias_printer - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_printer(list_t *node)
{
	char *p = NULL, *a = NULL;
	/*Check if the alias node is not NULL*/
	if (node)
	{
		/*Locate the position of '=' in the alias string*/
		p = locate_char(node->str, '=');
		/*Print the alias name up to the position of '='*/
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');/*to separate the alias name and value*/
		_printstr(p + 1);/*alias value strting from the char after'='*/
		_printstr("'\n");/*newline character to separate aliases*/
		return (0);
	}
	return (1);/*if the alias node is NULL, indicating an error*/
}

/**
 * copy_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int copy_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;
	/*If no arguments provided, print all aliases*/
	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_printer(node);
			node = node->next;
		}
		return (0);
	}
	/*Process each argument provided*/
	for (i = 1; info->argv[i]; i++)
	{
		p = locate_char(info->argv[i], '=');
		/*If '=' found, set alias*/
		if (p)
			alias_set(info, info->argv[i]);
		else
			/*print the corresponding alias*/
			alias_printer(prefix_node(info->alias, info->argv[i], '='));
	}

	return (0);
}
