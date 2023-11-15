#include "shell.h"

/**
 * check_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int check_cmd(info_t *info, char *path)
{
	struct stat st;
	/* Unused parameter; prevents compiler warnings */
	(void)info;
	/* Check if the path is NULL or if stat fails */
	if (!path || stat(path, &st))
		return (0);
	/* Check if the file is a regular file and is executable */
	if (st.st_mode & S_IFREG)
	{
		return (1);/* The file is an executable command */
	}
	return (0);/* The file is not an executable command */
}

/**
 * clone_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *clone_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;
	/* Validate the start and stop indices */
	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;/* Null-terminate the buffer */
	return (buf); /* Return a dynamically allocated buffer if needed */
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;
	/* Check if pathstr is NULL */
	if (!pathstr)
		return (NULL);
	if ((str_len(cmd) > 2) && is_prefix(cmd, "./"))
	{
		if (check_cmd(info, cmd))
			return (cmd);
	}
	/* Check if cmd is a relative path and executable */
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = clone_chars(pathstr, curr_pos, i);
			if (!*path)
				_strconcat(path, cmd);
			else
			{
				_strconcat(path, "/");
				_strconcat(path, cmd);
			}
			if (check_cmd(info, path))
				return (path);
			/* Check if the end of pathstr is reached */
			if (!pathstr[i])
				break;
			curr_pos = i;/*Update position for the next iteration*/
		}
		/* Move to the next character in pathstr */
		i++;
	}
	return (NULL);/* Return NULL if cmd is not found or on error */
}
