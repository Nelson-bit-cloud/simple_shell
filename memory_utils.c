#include "shell.h"

/**
 * free_pointer - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_pointer(void **ptr)
{
	/*Check if the pointer is not NULL and the pointed value is not NULL*/
	if (ptr && *ptr)
	{
		/* Free the memory and set the pointer to NULL */
		free(*ptr);
		*ptr = NULL;
		return (1);/* Return 1 to indicate successful freeing */
	}
	return (0);/* Return 0 if the pointer or the pointed value is NULL*/
}
