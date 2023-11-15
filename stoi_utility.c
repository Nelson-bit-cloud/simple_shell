#include "shell.h"

/**
 * is_interact - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_separator - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_separator(char c, char *delim)
{
	/*Iterate through delimiter string until 0 terminator is reached*/
	while (*delim)
		/*Check if current delimiter char matches given char*/
		if (*delim++ == c)
			return (1);/*indicate it's a delimiter*/
	return (0);/*indicate it's not a delimiter*/
}

/**
 *alpha_check - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int alpha_check(int c)
{
	/*Check range of lowercase or uppercase letters*/
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);/*alphabetic character*/
	else
		return (0);/*not an alphabetic character*/
}

/**
 *str_to_int - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int str_to_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		/*update the sign variable accordingly*/
		if (s[i] == '-')
			sign *= -1;
		/*If the char is a digit, update the result*/
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;/*Set flag to indicate end of the number*/
	}
	/*Adjust the output based on the sign*/
	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
