#include "shell.h"

/**
 **copy_string - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *copy_string(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	/*Copy char from source to destination up to the specified limit*/
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	/* Fill the remaining space with null characters if necessary */
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);/*Return the original address*/
}

/**
 **cat_str - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *cat_str(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	/* Find the end of the destination string */
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)/*Null-terminate the concatenated string if there is space*/
		dest[i] = '\0';
	return (s);/*Return the original address*/
}

/**
 **locate_char - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *locate_char(char *s, char c)
{
	do {
		/*Check if the current char matches the target char*/
		if (*s == c)
			return (s);/*Return a pointer to the current position*/
	} while (*s++ != '\0');/*until the end of the string is reached*/

	return (NULL);/*character is not found*/
}
