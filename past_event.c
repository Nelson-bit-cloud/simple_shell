#include "shell.h"

/**
 * read_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *read_history_file(info_t *info)
{
	char *buf, *dir;
	/* Retrieve the user's home directory */
	dir = retrieve_env(info, "HOME=");
	if (!dir)
		return (NULL);/*Return NULL if home directory is not found*/
	buf = malloc(sizeof(char) * (str_len(dir) + str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);/* Return NULL if memory allocation fails */
	buf[0] = 0;/* Initialize the buffer to an empty string */
	str_copy(buf, dir);/* Copy the home directory path to the buffer */
	_strconcat(buf, "/");/* Concatenate a '/' to the buffer */
	_strconcat(buf, HIST_FILE);
	return (buf);/* Return the constructed history file path */
}

/**
 * file_writer - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int file_writer(info_t *info)
{
	ssize_t fd;
	char *filename = read_history_file(info);
	list_t *node = NULL;
	/*Check if filename is NULL failure in getting the history file path*/
	if (!filename)
		return (-1);
	/* Iterate through the history list and write each entry to the file*/
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		fd_putstr(node->str, fd);
		fd_putchar('\n', fd);
	}
	fd_putchar(BUF_FLUSH, fd);
	close(fd); /* Close the file */
	return (1);/* Return 1 on success */
}

/**
 * show_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int show_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = read_history_file(info);
	/* Check filename is 0 failure in getting the history file path*/
	if (!filename)
		return (0);
	/* Open the file for reading */
	fd = open(filename, O_RDONLY);
	free(filename);/* Free the memory allocated for filename */
	if (fd == -1)/* Check if file opening is unsuccessful */
		return (0);
	if (!fstat(fd, &st))/* Get the size of the file using fstat */
		fsize = st.st_size;
	if (fsize < 2)/* Check if the file size is less than 2 bytes */
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;/* Null-terminate the buffer */
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;/* Null-terminate the line */
			history_list_add(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		history_list_add(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_at_index(&(info->history), 0);
	hist_renum(info);
	return (info->histcount);
}

/**
 * history_list_add - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int history_list_add(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;
	/*If the hist list is not empty, set node to point to the hist list*/
	if (info->history)
		node = info->history;
	append_node(&node, buf, linecount);
	/*If the hist list was empty,update info->hist to point the new node*/
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * hist_renum - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int hist_renum(info_t *info)
{
	list_t *node = info->history;
	int i = 0;
	/* Traverse the history linked list and renumber each node */
	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
