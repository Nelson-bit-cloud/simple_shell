#include "shell.h"

/**
 **set_memory - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *set_memory(char *s, char b, unsigned int n)
{
	unsigned int i;/* Loop counter */
	/*Loop through each byte in memory area & set it to constant byt*/
	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);/* Return a pointer to the memory area */
}

/**
 * free_str_arr - frees a string of strings
 * @pp: string of strings
 */
void free_str_arr(char **pp)
{
	char **a = pp;
	/* Check if the string of strings is NULL */
	if (!pp)
		return;
	while (*pp)/* Iterate through each string and free it */
		free(*pp++);
	free(a);/*Free the original pointer to the string of strings*/
}

/**
 * adjust_memory - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *adjust_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;/* Pointer to the new block */
	/* If ptr is NULL, allocate a new block with the new size */
	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	/* Allocate a new block with the new size */
	p = malloc(new_size);
	if (!p)
		return (NULL);
	/* Copy the contents from the old block to the new block */
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);/* Free the old block */
	return (p);/* Return the pointer to the new block */
}
