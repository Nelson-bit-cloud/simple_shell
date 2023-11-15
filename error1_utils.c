#include "shell.h"

/**
 * safe_stoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int safe_stoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;
	/* Iterate through the string characters */
	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)/*Check for integer overflow*/
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * show_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void show_error(info_t *info, char *estr)
{
	show_input(info->fname);
	show_input(": ");
	print_integer(info->line_count, STDERR_FILENO);
	show_input(": ");
	show_input(info->argv[0]);
	show_input(": ");
	show_input(estr);
}

/**
 * print_integer - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_integer(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;
	/* Set the putchar function to err_putchar for STDERR_FILENO*/
	if (fd == STDERR_FILENO)
		__putchar = err_putchar;
	if (input < 0)/*Handle negative input*/
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);/*Print the last digit*/
	count++;

	return (count);/*Return the number of characters printed*/
}

/**
 * itos_clone - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *itos_clone(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;
	/*Check if the num is negative and set the sign accordingly*/
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];/*Initialize the pointer to the end of the buffer*/
	*ptr = '\0';
	/*Convert the number to the specified base*/
	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	/* Add the sign if necessary */
	if (sign)
		*--ptr = sign;
	return (ptr);/*Return the pointer to the converted string*/
}

/**
 * erase_comment - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void erase_comment(char *buf)
{
	int i;
	/*Iterate through the string until the first '#' is found*/
	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			/* Replace '#' with '\0' to truncate the string */
			buf[i] = '\0';
			break;
		}
}
