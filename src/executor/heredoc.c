#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>

static t_type	file_to_token(t_fileflags flag)
{
	if (flag == INPUT_HEREDOC)
		return (DOUBLE_QUOTED);
	else if (flag == INPUT_HEREDOC_LIT)
		return (SINGLE_QUOTED);
	return (-1);
}

static int	parse_heredoc(t_file file, int fd)
{
	char	*line;
	t_list	*token;

	rl_clear_history();
	while (1)
	{
		line = readline(HEREDOC_PROMT);
		if (line == NULL || ft_strcmp(line, file.name) == 0)
		{
			free(line);
			return (0);
		}
		token = null_exit(ft_lstnew(create_token(line, \
			file_to_token(file.flag))));
		free(line);
		update_token_list(&token, expand_vars);
		ft_putendl_fd(((t_token *)token->content)->str, fd);
		ft_lstclear(&token, ((void (*))(void *)destroy_token));
	}
}

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
			return (file_name);
		free(num);
		free(file_name);
		i++;
	}
	return (NULL);
}

static int	handle_heredoc(t_file *file, t_list **created_files)
{
	pid_t	fork_id;
	int		exit_code;
	int		fd;
	char	*file_name;

	file_name = gen_filename();
	if (file_name == NULL)
	{
		print_error("minishell", "unable to create temp file", NULL);
		return (-1);
	}
	fork_id = fork();
	if (fork_id < 0)
		perror_exit("minishell", EXIT_FAILURE);
	if (fork_id == 0)
	{
		disable_signals();
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

int	heredoc_exec(t_list *commands, t_list **created_files)
{
	t_list	*files;
	t_file	*file;

	while (commands)
	{
		files = ((t_command *)commands->content)->files;
		while (files)
		{
			file = files->content;
			if (file->flag == INPUT_HEREDOC || file->flag == INPUT_HEREDOC_LIT)
			{
				if (handle_heredoc(file, created_files) < 0)
					return (1);
			}
			files = files->next;
		}
		commands = commands->next;
	}
	return (0);
}
