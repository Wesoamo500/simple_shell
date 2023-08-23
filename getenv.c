#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Returns the string array of the environment
 */
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: 1 on successful delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
    list_t *current_node = info->env;
    size_t current_index = 0;
    char *p;

    if (!current_node || !var)
        return 0;

    while (current_node)
    {
        p = starts_with(current_node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), current_index);
            current_index = 0;
            current_node = info->env;
            continue;
        }
        current_node = current_node->next;
        current_index++;
    }
    return info->env_changed;
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always returns 0
 */
int _setenv(info_t *info, char *var, char *value)
{
    char *env_entry = NULL;
    list_t *current_node;
    char *p;

    if (!var || !value)
        return 0;

    env_entry = malloc(_strlen(var) + _strlen(value) + 2);
    if (!env_entry)
        return 1;
    _strcpy(env_entry, var);
    _strcat(env_entry, "=");
    _strcat(env_entry, value);
    current_node = info->env;
    while (current_node)
    {
        p = starts_with(current_node->str, var);
        if (p && *p == '=')
        {
            free(current_node->str);
            current_node->str = env_entry;
            info->env_changed = 1;
            return 0;
        }
        current_node = current_node->next;
    }
    add_node_end(&(info->env), env_entry, 0);
    free(env_entry);
    info->env_changed = 1;
    return 0;
}
