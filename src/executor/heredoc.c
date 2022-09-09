#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>

static t_type	file_to_token(t_fileflags flag)
{
	if (flag == INPUT_HEREDOC)
		return (DOUBLE_QUOTED);
	else if (flag == INPUT_HEREDOC_LIT)
		return (SINGLE_QUOTED);
	return (-1);
}

static int	parse_heredoc(t_file file, int printfd)
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
		ft_putendl_fd(((t_token *)token->content)->str, printfd);
		ft_lstclear(&token, ((void (*))(void *)destroy_token));
	}
}

int	handle_heredoc(t_file file)
{
	pid_t	fork_id;
	int		pipe_fd[2];
	int		exit_code;

	if (pipe(pipe_fd) < 0)
		perror_exit("minishell", EXIT_FAILURE);
	fork_id = fork();
	if (fork_id < 0)
		perror_exit("minishell", EXIT_FAILURE);
	if (fork_id == 0)
	{
		close(pipe_fd[PIPE_IN_READ]);
		exit_code = parse_heredoc(file, pipe_fd[PIPE_OUT_WRITE]);
		close(pipe_fd[PIPE_OUT_WRITE]);
		exit(exit_code);
	}
	waitpid(fork_id, NULL, 0);
	close(pipe_fd[STDOUT_FILENO]);
	return (pipe_fd[STDIN_FILENO]);
}
