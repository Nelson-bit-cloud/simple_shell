#include "shell.h"

/**
 * str_len - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int str_len(char *s)
{
	int i = 0;
	/*Check if the string is NULL*/
	if (!s)
		return (0);
	/*Iterate through the characters until reaching the null terminator*/
	while (*s++)
		i++;
	return (i);
}

/**
 * str_cmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int str_cmp(char *s1, char *s2)
{
	/*Iterate through the characters of both strings*/
	while (*s1 && *s2)
	{
		if (*s1 != *s2)/*Compare the current characters*/
			return (*s1 - *s2);
		s1++;/*Move to the next characters*/
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * is_prefix - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *is_prefix(const char *haystack, const char *needle)
{
	while (*needle)/*Iterate through the characters of 'needle'*/
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strconcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strconcat(char *dest, char *src)
{
	char *ret = dest;/*Save the original address of 'dest'*/
	/*Move 'dest' to the end of the string*/
	while (*dest)/*Copy the characters from 'src' to 'dest'*/
		dest++;
	while (*src)
		*dest++ = *src++;/*Ensure null-termination in 'dest'*/
	*dest = *src;
	return (ret);/*Return the original address of 'dest'*/
}
