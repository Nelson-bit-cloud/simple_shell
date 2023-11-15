#include "shell.h"

/**
 * prepend_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *prepend_node(list_t **head, const char *str, int num)
{
	list_t *new_head;
	/* Check if the pointer to the head node is NULL */
	if (!head)
		return (NULL);
	/* Allocate memory for the new node */
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	set_memory((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;/* Set the num field of the new node */
	if (str)/* Duplicate the string if provided */
	{
		new_head->str = dup_str(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;/* Update the head pointer to point to the new node*/
	return (new_head);/* Return a pointer to the new head of the list */
}

/**
 * *append_node - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *append_node(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;
	/* Check if the pointer to the head node is NULL */
	if (!head)
		return (NULL);
	/* Create a new node and allocate memory for it */
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	set_memory((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)/* Duplicate the string if provided */
	{
		new_node->str = dup_str(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)/* If the list is not empty, traverse to the end */
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;/*If list is empty,make the new node head*/
	return (new_node);/* Return a pointer to the new node */
}

/**
 * print_str_list - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_str_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_printstr(h->str ? h->str : "(nil)");
		_printstr("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	/* Delete the first node if the index is 0 */
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	/* Traverse the list to find the node at the specified index */
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);/* Return 1 on success */
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);/* Return 0 if the index is out of bounds */
}

/**
 * clear_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void clear_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;
	/*Check if pointer to head node is NULL or if the list is empty*/
	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
