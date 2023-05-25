#include "builtins.h"

/**
 * __rnd_alias_add - add an rnd_alias to a list of rnd_aliases
 * @rnd_aliases: a pointer to a list of rnd_aliases
 * @name: the name of the rnd_alias
 * @value: the value of the rnd_alias
 */
void __rnd_alias_add(rnd_alias_t **rnd_aliases, const char *name, const char *value)
{
	rnd_alias_t *rnd_alias = get_dict_node(rnd_aliases ? *rnd_aliases : NULL, name);

	if (rnd_alias)
	{
		free(rnd_alias->rnd_val);
		rnd_alias->rnd_val = _strdup(value);
	}
	else
	{
		add_dict_node_end(rnd_aliases, name, value);
	}
}

/**
 * __rnd_alias_print - print an rnd_alias
 * @rnd_alias: the rnd_alias to print
 */
void __rnd_alias_print(rnd_alias_t *rnd_alias)
{
	write(STDOUT_FILENO, rnd_alias->rnd_key, _strlen(rnd_alias->rnd_key));
	write(STDOUT_FILENO, "='", 2);
	write(STDOUT_FILENO, rnd_alias->rnd_val, _strlen(rnd_alias->rnd_val));
	write(STDOUT_FILENO, "'\n", 2);
}

/**
 * __rnd_alias - create and display rnd_aliases
 * @rnd_info: rnd_info struct
 *
 * Return: status
 */
int __rnd_alias(rnd_info_t *rnd_info)
{
	rnd_alias_t *rnd_alias;
	char *name, **args = rnd_info->rnd_tokens + 1;
	ssize_t name_len;

	rnd_info->rnd_status = EXIT_SUCCESS;
	if (*args)
	{
		do {
			name_len = _strchr(*args, '=');
			if (name_len == -1)
			{
				rnd_alias = get_dict_node(rnd_info->rnd_aliases, *args);
				if (rnd_alias)
				{
					__rnd_alias_print(rnd_alias);
				}
				else
				{
					perrorl("not found", *rnd_info->rnd_tokens, *args, NULL);
					rnd_info->rnd_status = EXIT_FAILURE;
				}
			}
			else
			{
				name = _strndup(*args, name_len);
				__rnd_alias_add(&rnd_info->rnd_aliases, name, *args + name_len + 1);
				free(name);
			}
		} while (*++args);
	}
	else
	{
		for (rnd_alias = rnd_info->rnd_aliases; rnd_alias; rnd_alias = rnd_alias->next)
			__rnd_alias_print(rnd_alias);
	}
	return (rnd_info->rnd_status);
}