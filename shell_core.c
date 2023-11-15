#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;/* Variable to store the result of get_line */
	int builtin_ret = 0;
	/* Continue shell execution until an error occurs in get_line*/
	while (r != -1 && builtin_ret != -2)
	{
		init_info(info);/* Initialize the info_t struct */
		if (is_interact(info))
			_printstr("$ ");
		err_putchar(BUF_FLUSH);/* Flush the error buffer */
		r = get_line(info);/* Get a line of input from the user */
		/* Process the line only if there's no error in get_line */
		if (r != -1)
		{
			get_info(info, av);
			builtin_ret = locate_builtin(info);
			if (builtin_ret == -1)
				get_cmd(info);
		}
		else if (is_interact(info))
			_putchar('\n');
		delet_info(info, 0);
	}
	/* Write the command and its output to a file */
	file_writer(info);
	delet_info(info, 1);
	if (!is_interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);/*Return last built-in command*/
}

/**
 * locate_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int locate_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", shell_exit},
		{"env", env_output},
		{"help", get_help},
		{"history", get_history},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", cd_process},
		{"alias", copy_alias},
		{NULL, NULL}
	};

	/* Iterate through the array of built-in commands */
	for (i = 0; builtintbl[i].type; i++)
		if (str_cmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;/* Exit the loop after finding the match */
		}
	/* Return the result of the built-in command execution */
	return (built_in_ret);
}

/**
 * get_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void get_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;
	/*Increment line count if linecount_flag is set*/
	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	/*Count the number of non-separator characters in the argument*/
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_separator(info->arg[i], " \t\n"))
			k++;
	/*If no non-separator characters are found, return*/
	if (!k)
		return;
	/*Find the full path of the command in PATH*/
	path = find_path(info, retrieve_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		/*If interactive or absolute path, try finding in PATH again*/
		if ((is_interact(info) || retrieve_env(info, "PATH=")
			|| info->argv[0][0] == '/')
				&& find_path(info, retrieve_env(info, "PATH="), info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			show_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;
	/*Fork a child process*/
	child_pid = fork();
	/*Check for fork error*/
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	/*Code for child process*/
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, environ_copy(info)) == -1)
		{
			delet_info(info, 1);/*Handle execve error*/
			if (errno == EACCES)
				exit(126);/*Permission denied*/
			exit(1);/*Other execution error*/
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else/*Code for parent process*/
	{
		wait(&(info->status));/*Wait for the child process to finish*/
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				show_error(info, "Permission denied\n");
		}
	}
}
