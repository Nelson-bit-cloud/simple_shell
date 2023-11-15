#include "shell.h"

/**
 * chain_delim - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chain_delim(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;
	/* Check for "||" (logical OR) */
	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;/* Replace the first '|' with null */
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	/* Check for "&&" (logical AND) */
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;/* Replace the first '&' with null */
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);/* Not a chain delimiter */
	*p = j;
	return (1);/* Found a chain delimiter */
}

/**
 * chain_check - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void chain_check(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;
	/* Check for CMD_AND */
	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;/* Move to the end of the buffer */
		}
	}
	if (info->cmd_buf_type == CMD_OR)/* Check for CMD_OR */
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;/* Move to the end of the buffer */
		}
	}

	*p = j;
}

/**
 * alias_sub - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int alias_sub(info_t *info)
{
	int i;
	list_t *node;
	char *p;
	/* Find alias in the alias list */
	for (i = 0; i < 10; i++)
	{
		node = prefix_node(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);/* Free the original command */
		p = locate_char(node->str, '=');
		if (!p)
			return (0);
		p = dup_str(p + 1);
		if (!p)/* Set the replacement command as the new command */
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * vars_subs - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int vars_subs(info_t *info)
{
	int i = 0;
	list_t *node;
	 /* Check if the arg starts with '$' and has a following char*/
	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		/* Substitute $? with the exit status */
		if (!str_cmp(info->argv[i], "$?"))
		{
			string_sub(&(info->argv[i]),
				dup_str(itos_clone(info->status, 10, 0)));
			continue;
		}
		/* Substitute $$ with the process ID */
		if (!str_cmp(info->argv[i], "$$"))
		{
			string_sub(&(info->argv[i]),
				dup_str(itos_clone(getpid(), 10, 0)));
			continue;
		}
		/* Substitute environment variables */
		node = prefix_node(info->env, &info->argv[i][1], '=');
		if (node)
		{
			string_sub(&(info->argv[i]),
				dup_str(locate_char(node->str, '=') + 1));
			continue;
		}
		string_sub(&info->argv[i], dup_str(""));

	}
	return (0);
}

/**
 * string_sub - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int string_sub(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
