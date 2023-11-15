#include "shell.h"

/**
 * str_copy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *str_copy(char *dest, char *src)
{
	int i = 0;
	/*Check for self-copy or null source*/
	if (dest == src || src == 0)
		return (dest);
	while (src[i])/*Copy characters until null terminator*/
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;/*Null-terminate the destination string*/
	return (dest);
}

/**
 * dup_str - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *dup_str(const char *str)
{
	int length = 0;
	char *ret;
	/*Check for null input*/
	if (str == NULL)
		return (NULL);
	/*Calculate the length of the input string*/
	while (*str++)
		length++;
	/*Allocate memory for the duplicated string*/
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	/*Copy characters to the duplicated string*/
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _printstr - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _printstr(char *str)
{
	int i = 0;
	/*Check for null input*/
	if (!str)
		return;
	while (str[i] != '\0')/*Print each character of the string*/
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	/*Check if the character is BUF_FLUSH or the buffer is ful*/
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		/*Write the buffer to stdout*/
		write(1, buf, i);
		i = 0;/*Reset the buffer index*/
	}
	/*Check if the character is not BUF_FLUSH*/
	if (c != BUF_FLUSH)
		buf[i++] = c;/*Add the character to the buffer*/
	return (1);
}
