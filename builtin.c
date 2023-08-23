#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
    int ex_check;

    if (info->argv[1]) // If there is an exit argument
    {
        ex_check = _erratoi(info->argv[1]);
        if (ex_check == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }
        info->err_num = ex_check;
        return -2;
    }
    else
    {
        info->err_num = -1;
        return -2;
    }
}

/**
 * _mycd - Changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
    char *current_dir, *target_dir, buffer[1024];
    int chdir_result;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
    {
        _puts("TODO: >>getcwd failure emsg here<<\n");
    }

    if (!info->argv[1])
    {
        target_dir = _getenv(info, "HOME=");
        if (!target_dir)
        {
            target_dir = _getenv(info, "PWD=");
        }
        chdir_result = chdir(target_dir ? target_dir : "/");
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(current_dir);
            _putchar('\n');
            return 1;
        }
        _puts(_getenv(info, "OLDPWD="));
        _putchar('\n');
        target_dir = _getenv(info, "OLDPWD=");
        chdir_result = chdir(target_dir ? target_dir : "/");
    }
    else
    {
        chdir_result = chdir(info->argv[1]);
    }

    if (chdir_result == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}

/**
 * _myhelp - Displays help information
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
    char **arguments;

    arguments = info->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arguments); /* Temp att_unused workaround */
    return 0;
}
