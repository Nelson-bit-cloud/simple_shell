#include "shell.h"

/**
 * show_input - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void show_input(char *str)
{
	int i = 0;
	/*Check if the input string is NULL*/
	if (!str)
		return;
	while (str[i] != '\0')
	{
		err_putchar(str[i]);
		i++;
	}
}

/**
 * err_putchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int err_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	/*If the character is BUF_FLUSH or full, flush the buffer*/
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);/* Write the buffer to stderr */
		i = 0;/* Reset the buffer index */
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);/* Return 1 on success */
}

/**
 * fd_putchar - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int fd_putchar(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	/*If the character is BUF_FLUSH/the buffer is full, flush the buffer*/
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);/*specified file descriptor*/
		i = 0;/* Reset the buffer index */
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);/*Return 1 on success*/
}

/**
 * fd_putstr - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int fd_putstr(char *str, int fd)
{
	int i = 0;
	/* Check if the input string is NULL */
	if (!str)
		return (0);
	while (*str)
	{
		i += fd_putchar(*str++, fd);
	}
	return (i);/*Return the number of characters put*/
}
