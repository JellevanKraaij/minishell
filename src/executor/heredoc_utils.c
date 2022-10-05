/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:15 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:15 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <stdio.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <signal.h>

static char	*gen_filename(void)
{
	char	*file_name;
	char	*num;
	size_t	i;

	i = 0;
	while (i < INT_MAX)
	{
		num = null_exit(ft_itoa(i));
		file_name = null_exit(ft_strjoin(HEREDOC_FILENAME, num));
		if (access(file_name, F_OK) < 0)
		{
			free(num);
			return (file_name);
		}
		free(num);
		free(file_name);
		i++;
	}
	return (NULL);
}

static int	parse_heredoc(t_file file, int fd)
{
	char	*line;
	char	*tmp;

	rl_clear_history();
	while (1)
	{
		line = readline(HEREDOC_PROMT);
		if (line == NULL || ft_strcmp(line, file.name) == 0)
		{
			free(line);
			return (0);
		}
		if (file.flag == INPUT_HEREDOC)
		{
			tmp = expand_vars_string(line, DOUBLE_QUOTED);
			free(line);
			line = tmp;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static int	heredoc_fork_process(char *file_name, t_file *file, \
			t_list **created_files)
{
	pid_t	fork_id;
	int		exit_code;
	int		fd;

	fork_id = fork();
	if (fork_id < 0)
		perror_exit("minishell", EXIT_FAILURE);
	if (fork_id == 0)
	{
		disable_signals();
		signal(SIGQUIT, SIG_IGN);
		fd = open(file_name, O_CREAT | O_WRONLY, 0644);
		if (fd < 0)
			perror_exit("minishell", 1);
		exit_code = parse_heredoc(*file, fd);
		close(fd);
		exit(exit_code);
	}
	free(file->name);
	file->name = file_name;
	ft_lstadd_back(created_files, \
					null_exit(ft_lstnew(null_exit(ft_strdup(file_name)))));
	if (wait_for_childs(1, fork_id) > 0)
		return (-1);
	return (0);
}

int	handle_heredoc(t_file *file, t_list **created_files)
{
	char	*file_name;

	file_name = gen_filename();
	if (file_name == NULL)
	{
		print_error("minishell", "unable to create temp file", NULL);
		return (-1);
	}
	return (heredoc_fork_process(file_name, file, created_files));
}
