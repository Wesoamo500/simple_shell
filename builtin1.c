#include "shell.h"

/**
 * _myhistory - Displays the history list, one command per line, with line
 *              numbers starting from 0.
 * @info: Pointer to a structure containing potential arguments. Used to
 *        maintain a constant function prototype.
 *
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return 0;
}


/**
 * unset_alias - Unsets an alias by removing it from the alias list.
 * @info: Pointer to a parameter struct.
 * @str: The string representing the alias to be unset.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *equal_position;
    char saved_char;
    int return_value;

    equal_position = _strchr(str, '=');
    if (!equal_position)
    {
        return 1; // No '=' character found, indicating an error
    }

    saved_char = *equal_position; // Save the character at the equal position
    *equal_position = '\0'; // Temporarily set '=' to a null terminator

    // Find and delete the node corresponding to the alias in the alias list
    if (info->alias)
    {
        int index = get_node_index(info->alias, node_starts_with(info->alias, str, -1));
        return_value = delete_node_at_index(&(info->alias), index);
    }
    else
    {
        return_value = 1; // Error: No alias list to remove from
    }

    *equal_position = saved_char; // Restore the original character
    return return_value;
}


/**
 * set_alias - Adds or updates an alias.
 * @info: Pointer to a parameter struct.
 * @alias_str: The string containing the alias.
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *alias_str)
{
    char *equal_position;

    equal_position = _strchr(alias_str, '=');
    if (!equal_position)
    {
        return 1; // No '=' character found, indicating an error
    }

    if (!*++equal_position)
    {
        return unset_alias(info, alias_str);
    }

    unset_alias(info, alias_str);
    return add_node_end(&(info->alias), alias_str, 0) == NULL;
}

/**
 * print_alias - Prints an alias string.
 * @node: Pointer to the alias node.
 *
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *equal_position = NULL, *alias_name = NULL;

    if (node)
    {
        equal_position = _strchr(node->str, '=');
        for (alias_name = node->str; alias_name <= equal_position; alias_name++)
        {
            _putchar(*alias_name);
        }
        _putchar('\'');
        _puts(equal_position + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * _myalias - Mimics the alias builtin (man alias).
 * @info: Pointer to a parameter struct.
 *
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
    int i = 0;
    char *equal_position = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    while (info->argv[i])
    {
        equal_position = _strchr(info->argv[i], '=');
        if (equal_position)
        {
            set_alias(info, info->argv[i]);
        }
        else
        {
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
        }
        i++;
    }

    return 0;
}
