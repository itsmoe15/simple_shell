#include "shell.h"
#include "hsh.h"
#ifndef _QUOTE_H_
#define _QUOTE_H_

#include <stdlib.h>
#include "quote.h"
#include "ctype.h"
#include "tokens.h"
#include "string.h"
#ifndef _TYPES_H_
#define _TYPES_H_
#ifndef _STRING_H_
#define _STRING_H_
#include "command.h"
#include <stdlib.h>
#include <stdarg.h>
#ifndef PATH_H
#define PATH_H
#ifndef LIST_H
#define LIST_H
#ifndef _INFO_H_
#define _INFO_H_
#define GETLINE_BUFFER_SIZE 4096
#define GETLINE_TABLE_SIZE 127
#ifndef _ERROR_H_
#define _ERROR_H_
#define HELP_HELP "help [BUILTIN]"
#define HELP_DESC
#define EXIT_HELP "exit [STATUS]"
#define EXIT_DESC
#define EXEC_HELP "exec COMMAND [ARGS ...]"
#define EXEC_DESC
#define ALIAS_HELP "alias [KEY[=VALUE] ...]"
#define ALIAS_DESC
#ifndef _BUILTINS_H_
#define _BUILTINS_H_
ifndef _ALIAS_H_
#define _ALIAS_H_

#include "dict.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include "alias.h"
#include "command.h"
#include "env.h"
#include "error.h"
#include "getline.h"
#include "history.h"
#include "list.h"
#include "string.h"
#include "tokens.h"
#include "types.h"



#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#ifndef SHELL_H
#define SHELL_H
#define UNSETENV_HELP "unsetenv NAME"
#define UNSETENV_DESC
#define SETENV_HELP "setenv [NAME [VALUE]]"
#define SETENV_DESC


#ifndef _ENV_H_
#define _ENV_H_
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#include "info.h"
#include "list.h"
#include "string.h"
#include "types.h"
ifndef _CTYPE_H_
#define _CTYPE_H_

#include <stdbool.h>
#include <stdlib.h>

bool _isalnum(int c);
bool _isalpha(int c);
bool _isdigit(int c);
bool _isident(int c);
bool _isspace(int c);
bool _isquote(int c);

bool _isnumber(const char *s);
typedef enum cmdlist_sep_n;

int interactive;
	int argc;
	char **argv;
	char *file;
	int fileno;
	int status;
	char *line;
	size_t lineno;
	char **tokens;
	pid_t pid;
	char *cwd;
	char *exe;
	env_t *env;
	list_t *path;
	alias_t *aliases;
	history_t *history;
	cmdlist_t *commands;
typedef buf_table_node_t *buf_table_t[GETLINE_TABLE_SIZE];
void perrorl(const char *msg, ...);
void perrorl_default(const char *arg0, size_t lineno, const char *msg, ...);
extern char **environ;
bool read_input(info_t *info);
char buffer[GETLINE_BUFFER_SIZE];
quote_state_t _read_input(char **lineptr, int fd);
typedef dict_t env_t;

env_t *env_to_dict(char **env);
env_t *_env_to_dict(env_t **tailptr, char **env);
char **dict_to_env(env_t *head);

int parse(info_t *info);

int execute(info_t *info);
int _execute(info_t *info);

void expand_aliases(alias_t *aliases, char ***tokptr);
char *expand_alias(alias_t *aliases, char ***tokptr);

void expand_vars(info_t *info, char ***tokptr);
char **_expand_vars(info_t *info, char ***tokptr);
cmdlist_t *cmd_to_list(const char *cmd);
cmdlist_t *_cmd_to_list(cmdlist_t **tailptr, char *split, size_t count);

size_t split_cmd(char *cmd);

cmdlist_t *add_cmd_end(cmdlist_t **headptr, const char *cmd);
cmdlist_t *del_cmd(cmdlist_t **headptr, size_t index);
char **pop_cmd(cmdlist_t **headptr);
void free_cmdlist(cmdlist_t **headptr);

cmdtree_t *cmd_to_tree(const char * const *tokens);
void free_cmdtree(cmdtree_t **rootptr);
const struct builtin *get_builtin(const char *name);
const struct builtin *get_builtins(void);

int __alias(info_t *info);
int __cd(info_t *info);
int __env(info_t *info);
int __exec(info_t *info);
int __exit(info_t *info);
int __help(info_t *info);
int __history(info_t *info);
int __setenv(info_t *info);
int __unsetenv(info_t *info);

typedef int (*builtin_fp)(info_t *);
void remove_comments(cmdlist_t *cmd);

void open_script(info_t *info);

void _sigint(int signal);
char *search_path(info_t *info, list_t *path);
char *search_path(info_t *info, list_t *path);
int parse(info_t *info);
list_t *str_to_list(const char *str, char delim);
list_t *_str_to_list(list_t **tailptr, const char *str, char delim);
list_t *add_node(list_t **headptr, const char *str);
list_t *add_node_end(list_t **headptr, const char *str);
void free_list(list_t **headptr);

ssize_t _memchr(const void *src, unsigned char chr, size_t n);
void *_memcpy(void *dest, const void *src, size_t n);
void *_memdup(const void *src, size_t n);
void *_memset(void *dest, unsigned char chr, size_t n);

ssize_t _strchr(const char *str, char chr);
ssize_t _strnchr(const char *str, char chr, size_t n);

int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, size_t n);

char *_strdup(const char *str);
char *_strndup(const char *str, size_t n);

ssize_t _strlen(const char *str);
ssize_t _strnlen(const char *str, size_t n);

char *strjoin(size_t *n, const char *sep, const char *pre, const char *suf);
char *strjoina(size_t *n, const char *sep, const char **array);
char *strjoinl(size_t *n, const char *sep, ...);

unsigned int atou(char *s);
char *num_to_str(size_t n);

char *strjoin(size_t *n, const char *sep, const char *pre, const char *suf);
char **tokenize(const char *str);
ssize_t _strnchr(const char *str, char chr, size_t n);
char *strjoin(size_t *n, const char *sep, const char *pre, const char *suf);
ssize_t _strchr(const char *str, char chr);
size_t split_cmd(char *cmd);
void remove_comments(cmdlist_t *cmd);
typedef enum quote_state;
quote_state_t quote_state(char c);

#endif

