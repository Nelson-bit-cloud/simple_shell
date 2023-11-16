#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shcore.c */
int hsh(info_t *, char **);
int locate_builtin(info_t *);
void get_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_textparser.c */
int check_cmd(info_t *, char *);
char *clone_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errorsutils.c */
void show_input(char *);
int err_putchar(char);
int fd_putchar(char c, int fd);
int fd_putstr(char *str, int fd);

/* toem_str_utils.c */
int str_len(char *);
int str_cmp(char *, char *);
char *is_prefix(const char *, const char *);
char *_strconcat(char *, char *);

/* toem_stri1_utils.c */
char *str_copy(char *, char *);
char *dup_str(const char *);
void _printstr(char *);
int _putchar(char);

/* toem_exits_handling.c */
char *copy_string(char *, char *, int);
char *cat_str(char *, char *, int);
char *locate_char(char *, char);

/* toem_tokenizer_utils.c */
char **split_words(char *, char *);
char **split_words2(char *, char);

/* toem_realloc.c */
char *set_memory(char *, char, unsigned int);
void free_str_arr(char **);
void *adjust_memory(void *, unsigned int, unsigned int);

/* toem_memory_utils.c */
int free_pointer(void **);

/* toem_stoi_utility.c */
int is_interact(info_t *);
int is_separator(char, char *);
int alpha_check(int);
int str_to_int(char *);

/* toem_errors1_utils.c */
int safe_stoi(char *);
void show_error(info_t *, char *);
int print_integer(int, int);
char *itos_clone(long int, int, int);
void erase_comment(char *);

/* toem_builtin_utils.c */
int shell_exit(info_t *);
int cd_process(info_t *);
int get_help(info_t *);

/* toem_builtin1_utils.c */
int get_history(info_t *);
int assign_alias(info_t *);
int copy_alias(info_t *);
int execute_ls(info_t *info);

/*toem_readline.c */
ssize_t get_line(info_t *);
int read_line(info_t *, char **, size_t *);
void siginit_handler(int);

/* toem_info_fetcher.c */
void init_info(info_t *);
void get_info(info_t *, char **);
void delet_info(info_t *, int);

/* toem_env_utils.c */
char *retrieve_env(info_t *, const char *);
int env_output(info_t *);
int set_env(info_t *);
int unset_env(info_t *);
int built_env_list(info_t *);

/* toem_env_handling.c */
char **environ_copy(info_t *);
int del_env(info_t *, char *);
int init_env(info_t *, char *, char *);

/* toem_past_event.c */
char *read_history_file(info_t *info);
int file_writer(info_t *info);
int show_history(info_t *info);
int history_list_add(info_t *info, char *buf, int linecount);
int hist_renum(info_t *info);

/* toem_data_lists.c */
list_t *prepend_node(list_t **, const char *, int);
list_t *append_node(list_t **, const char *, int);
size_t print_str_list(const list_t *);
int delete_at_index(list_t **, unsigned int);
void clear_list(list_t **);

/* toem_data_lists1.c */
size_t list_size(const list_t *);
char **list_str(list_t *);
size_t display_list(const list_t *);
list_t *prefix_node(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);

/* toem_data_vars.c */
int chain_delim(info_t *, char *, size_t *);
void chain_check(info_t *, char *, size_t *, size_t, size_t);
int alias_sub(info_t *);
int vars_subs(info_t *);
int string_sub(char **, char *);

#endif
