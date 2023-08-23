#include "shell.h"
/**
 * _strncpy - Copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 *
 * Return: The concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
    int i;
    char *result = dest;

    for (i = 0; src[i] != '\0' && i < n - 1; i++)
    {
        dest[i] = src[i];
    }

    if (i < n)
    {
        int j;
        for (j = i; j < n; j++)
        {
            dest[j] = '\0';
        }
    }
    return result;
}

/**
 * _strncat - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * Return: The concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
    int i, j;
    char *result = dest;

    for (i = 0; dest[i] != '\0'; i++)
    {
    }

    for (j = 0; src[j] != '\0' && j < n; j++)
    {
        dest[i + j] = src[j];
    }

    if (j < n)
    {
        dest[i + j] = '\0';
    }
    return result;
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area s.
 */
char *_strchr(char *s, char c)
{
    do
    {
        if (*s == c)
            return s;
    } while (*s++ != '\0');

    return NULL;
}
