#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;
	/* Modify the file descriptor using inline assembly */
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));
	/* If a command-line argument is provided, open the file */
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				show_input(av[0]);
				show_input(": 0: Can't open ");
				show_input(av[1]);
				err_putchar('\n');
				err_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	/* Initialize environment variables list and get history */
	}
	built_env_list(info);
	get_history(info);
	/* Call the hsh function with the provided information */
	hsh(info, av);
	return (EXIT_SUCCESS);
}
