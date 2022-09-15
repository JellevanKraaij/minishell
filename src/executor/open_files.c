#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

void	delete_files(t_list **created_files)
{
	t_list	*iterate;

	iterate = *created_files;
	while (iterate)
	{
		if (unlink(iterate->content) < 0)
			perror("minishell");
		iterate = iterate->next;
	}
	ft_lstclear(created_files, free);
}

static void	dup_file(int fd, int dir)
{
	if (dup2(fd, dir) < 0)
		perror_exit("minishell", 1);
}

static int	fileflag_to_fd(t_fileflags flag)
{
	if (flag == INPUT || flag == INPUT_HEREDOC || flag == INPUT_HEREDOC_LIT)
		return (FILE_IN);
	if (flag == OUTPUT || flag == OUTPUT_APP)
		return (FILE_OUT);
	return (-1);
}

static int	open_file(t_file file)
{
	int	fd;

	if (file.flag == INPUT)
		fd = open(file.name, O_RDONLY);
	else if (file.flag == OUTPUT)
		fd = open(file.name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (file.flag == OUTPUT_APP)
		fd = open(file.name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (file.flag == INPUT_HEREDOC || file.flag == INPUT_HEREDOC_LIT)
		fd = open(file.name, O_RDONLY);
	else
	{
		print_error("minishell", "invalid fileflag", NULL);
		exit (1);
	}
	return (fd);
}

int	open_dup_files(t_list *files)
{
	t_file	file;
	int		fd;

	while (files)
	{
		file = *(t_file *)files->content;
		fd = open_file(file);
		if (fd < 0)
		{
			print_error("minishell", file.name, strerror(errno));
			return (1);
		}
		dup_file(fd, fileflag_to_fd(file.flag));
		if (fd != fileflag_to_fd(file.flag))
			close(fd);
		files = files->next;
	}
	return (0);
}
