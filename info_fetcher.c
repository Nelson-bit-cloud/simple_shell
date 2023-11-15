#include "shell.h"

/**
 * init_info - initializes info_t struct
 * @info: struct address
 */
void init_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * get_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void get_info(info_t *info, char **av)
{
	int i = 0;
	/* Set the program name in the info struct */
	info->fname = av[0];
	if (info->arg)
	{
		info->argv = split_words(info->arg, " \t");
		if (!info->argv)
		{
			/*Split arg str into arr of words using spaces & tabs as delimiters*/
			info->argv = split_words(info->arg, " \t");
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = dup_str(info->arg);
				info->argv[1] = NULL;
			}
		}
		/* Count the number of elements in the argument array */
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;/*Set the argument count in the info struct*/

		alias_sub(info);/* Perform alias substitution */
		vars_subs(info);/* Perform variable substitution */
	}
}

/**
 * delet_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void delet_info(info_t *info, int all)
{
	free_str_arr(info->argv);/* Free the argument vector */
	info->argv = NULL;/* Set the argument vector pointer to NULL */
	info->path = NULL;/* Set the path pointer to NULL */
	if (all)
	{
		/*free the argument string if cmd_buf is not set*/
		if (!info->cmd_buf)
			free(info->arg);
		/* Clear the environment linked list */
		if (info->env)
			clear_list(&(info->env));
		/* Clear the history linked list */
		if (info->history)
			clear_list(&(info->history));
		/* Clear the alias linked list */
		if (info->alias)
			clear_list(&(info->alias));
		/* Free the environment array */
		free_str_arr(info->environ);
			info->environ = NULL;
		/* Free the command buffer pointer */
		free_pointer((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		/* Flush the buffer for characters written to stderr */
		_putchar(BUF_FLUSH);
	}
}
