#include "shell.h"

/**
 * shell_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int shell_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /*If there is an exit argument*/
	{
		exitcheck = safe_stoi(info->argv[1]);
		if (exitcheck == -1)/*If safe_stoi returns -1*/
		{
			info->status = 2;
			show_error(info, "Illegal number: ");
			show_input(info->argv[1]);
			err_putchar('\n');
			return (1);/*set error status, show error & return 1*/
		}
		info->err_num = safe_stoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * cd_process - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int cd_process(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);/*Get the current working directory*/
	if (!s)
		_printstr("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = retrieve_env(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = retrieve_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!retrieve_env(info, "OLDPWD="))
		{
			_printstr(s);
			_putchar('\n');
			return (1);
		}
		_printstr(retrieve_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = retrieve_env(info, "OLDPWD=")) ? dir : "/");
	}
	else/*Change to the specified directory*/
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		show_error(info, "can't cd to ");
		show_input(info->argv[1]), err_putchar('\n');
	}
	else
	{
		init_env(info, "OLDPWD", retrieve_env(info, "PWD="));
		init_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * get_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int get_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;

	_printstr("help call works. Function not yet implemented \n");
	/* Temporarily avoid unused variable warning */
	if (0)
		_printstr(*arg_array);
	return (0);
}
/**
 * execute_ls - able to show list of files in working directory
 * @info: Structure containing potential arguments. Used to maintain
 *		constant function prototype.
 * Return: Always 0
 */
int execute_ls(info_t *info)
{
	int status = system("/bin/ls");

	/* Check if there are any arguments for ls (e.g., ls -l)*/
	if (info->argc > 1)
	{
		fprintf(stderr, "ls: too many arguments\n");
		return (1);/* Return 1 to indicate failure*/
	}

	/* Check the exit status of the system call */
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		return (0);/* Return 0 to indicate success*/
	}
	else
	{
		fprintf(stderr, "ls: command failed\n");
		return (1);/*Return 1 to indicate failure*/
	}
}
