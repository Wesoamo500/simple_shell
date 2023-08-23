#include "shell.h"

/**
 * _eputs - Prints a string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
    int index = 0;

    if (!str)
        return;

    while (str[index] != '\0')
    {
        _eputchar(str[index]);
        index++;
    }
}

/**
 * _eputchar - Writes a character to stderr.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
    static int i;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buffer, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buffer[i++] = c;

    return 1;
}

/**
 * _putfd - Writes a character to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
    static int i;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buffer, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buffer[i++] = c;

    return 1;
}

/**
 * _putsfd - Prints a string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
    int chars_written = 0;

    if (!str)
        return 0;

    while (*str)
    {
        chars_written += _putfd(*str++, fd);
    }
    return chars_written;
}
