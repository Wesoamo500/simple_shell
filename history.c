#include "shell.h"
/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
	char *file_buf, *home_dir;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);
	file_buf = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!file_buf)
		return (NULL);
	file_buf[0] = '\0';
	_strcpy(file_buf, home_dir);
	_strcat(file_buf, "/");
	_strcat(file_buf, HIST_FILE);
	return (file_buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *hist_filename = get_history_file(info);
	list_t *node = NULL;

	if (!hist_filename)
		return (-1);

	fd = open(hist_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(hist_filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t fd, read_len, file_size = 0;
	struct stat st;
	char *buf = NULL, *hist_filename = get_history_file(info);

	if (!hist_filename)
		return (0);

	fd = open(hist_filename, O_RDONLY);
	free(hist_filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (file_size + 1));
	if (!buf)
		return (0);
	read_len = read(fd, buf, file_size);
	buf[file_size] = '\0';
	if (read_len <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < file_size; i++)
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, line_count++);
	free(buf);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @line_count: the history line count, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
