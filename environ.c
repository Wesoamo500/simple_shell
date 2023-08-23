#include "shell.h"

/**
 * _myenv - Prints the current environment.
 * @info: Pointer to a parameter struct.
 *
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
    print_list_str(info->env);
    return 0;
}

/**
 * _getenv - Gets the value of an environment variable.
 * @info: Pointer to a parameter struct.
 * @name: Name of the environment variable.
 *
 * Return: Pointer to the value of the environment variable.
 */
char *_getenv(info_t *info, const char *name)
{
    list_t *env_node = info->env;
    char *value;

    while (env_node)
    {
        value = starts_with(env_node->str, name);
        if (value && *value)
            return value;
        env_node = env_node->next;
    }

    return NULL;
}

/**
 * _mysetenv - Sets or modifies an environment variable.
 * @info: Pointer to a parameter struct.
 *
 * Return: 0 on success, 1 on error.
 */
int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return 0;
    return 1;
}

/**
 * _myunsetenv - Removes an environment variable.
 * @info: Pointer to a parameter struct.
 *
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
    int i = 1;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }

    while (info->argv[i])
    {
        _unsetenv(info, info->argv[i]);
        i++;
    }

    return 0;
}

/**
 * populate_env_list - Populates the environment linked list.
 * @info: Pointer to a parameter struct.
 *
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
    list_t *env_list = NULL;
    size_t i = 0;

    while (environ[i])
    {
        add_node_end(&env_list, environ[i], 0);
        i++;
    }

    info->env = env_list;
    return 0;
}
