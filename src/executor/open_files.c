#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include <stdio.h>
#include <fcntl.h>

static void	dup_file(int fd, int dir)
{
	if (dup2(fd, dir) < 0)
		perror_exit("minishell", 1);
}

static int	check_fd(int fd, char *name)
{
	if (fd < 0)
	{
		print_error("minishell", name, "no such file or directory");
		exit (1);
	}
	return (fd);
}

static int	fileflag_to_fd(t_fileflags flag)
{
	if (flag == INPUT)
		return (FILE_IN);
	if (flag == OUTPUT)
		return (FILE_OUT);
	return (-1);
}

void	open_dup_file(void *file_pointer)
{
	t_file	file;
	int		fd;

	file = *((t_file *)file_pointer);
	if (file.flag == INPUT)
		fd = check_fd(open(file.name, O_RDONLY), file.name);
	else if (file.flag == OUTPUT)
		fd = check_fd(open(file.name, O_CREAT | O_WRONLY | O_TRUNC, 0644), \
							file.name);
	else if (file.flag == OUTPUT_APP)
		fd = check_fd(open(file.name, O_CREAT | O_WRONLY | O_APPEND, 0644), \
							file.name);
	else
	{
		print_error("minishell", "invalid fileflag", NULL);
		exit(1);
	}
	dup_file(fd, fileflag_to_fd(file.flag));
	if (fd != fileflag_to_fd(file.flag))
		close(fd);
}