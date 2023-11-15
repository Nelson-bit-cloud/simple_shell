#include "shell.h"

/**
 * list_size - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_size(const list_t *h)
{
	size_t i = 0;
	/* Traverse the linked list and count the number of nodes */
	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);/* Return the size of the linked list */
}

/**
 * list_str - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_str(list_t *head)
{
	list_t *node = head;
	size_t i = list_size(head), j;
	char **strs;
	char *str;
	/* Check if the linked list is empty */
	if (!head || !i)
		return (NULL);
	/* Allocate memory for the array of strings */
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		/* Copy the string and assign it to the array */
		str = str_copy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;/* Return the array of strings */
	return (strs);/* Null-terminate the array of strings */
}


/**
 * display_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t display_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_printstr(itos_clone(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_printstr(h->str ? h->str : "(nil)");
		_printstr("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * prefix_node - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *prefix_node(list_t *node, char *prefix, char c)
{
	char *p = NULL;
	/* Traverse the linked list */
	while (node)
	{
		p = is_prefix(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);/* Return the matching node */
}

/**
 * node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t node_index(list_t *head, list_t *node)
{
	size_t i = 0;
	/* Traverse the linked list */
	while (head)
	{
		if (head == node)
			return (i);/* Return the index if the node is found*/
		head = head->next;
		i++;
	}
	return (-1);/* Return -1 if the node is not found in the list */
}
