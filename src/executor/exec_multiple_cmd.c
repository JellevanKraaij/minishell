#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include "environment.h"
#include <stdio.h>

static void	exec_multiple_cmd(t_command *cmd)
{
	char		*path;
	t_builtin_f	builtin_function;

	disabler_signals();
	g_last_exit_code = 0;
	ft_lstiter(cmd->files, open_dup_file);
	if (!cmd->argv)
		exit (0);
	builtin_function = lookup_builtin(cmd->argv[0]);
	if (builtin_function != NULL)
		exit(execute_builtin(cmd, builtin_function));
	path = find_path(cmd->argv[0]);
	if (path == NULL)
	{
		print_error("minishell", cmd->argv[0], "command not found");
		exit(127);
	}
	if (execve(path, cmd->argv, ft_getenviron()) < 0)
		perror_exit("minishell", EXIT_FAILURE);
}

void	first_cmd(t_command *cmd, int pipe_out[2])
{
	int	fork_id;

	fork_id = fork();
	if (fork_id < 0)
		perror_exit("minishell", EXIT_FAILURE);
	if (fork_id == 0)
	{
		if (dup2(pipe_out[PIPE_OUT_WRITE], STDOUT_FILENO) < 0)
			perror_exit("minishell", 1);
		close(pipe_out[PIPE_OUT_WRITE]);
		close(pipe_out[PIPE_IN_READ]);
		exec_multiple_cmd(cmd);
	}
	close(pipe_out[PIPE_OUT_WRITE]);
}

void	mid_cmd(t_command *cmd, int pipe_in, int pipe_out[2])
{
	int	fork_id;

	fork_id = fork();
	if (fork_id < 0)
		print_error("minishell", "fork", "error");
	if (fork_id == 0)
	{
		if (dup2(pipe_out[PIPE_OUT_WRITE], STDOUT_FILENO) < 0 || \
				dup2(pipe_in, STDIN_FILENO) < 0)
			perror_exit("minishell", EXIT_FAILURE);
		close(pipe_in);
		close(pipe_out[PIPE_OUT_WRITE]);
		close(pipe_out[PIPE_IN_READ]);
		exec_multiple_cmd(cmd);
	}
	close(pipe_in);
	close(pipe_out[PIPE_OUT_WRITE]);
}

int	final_cmd(t_command *cmd, int pipe_in)
{
	int	fork_id;

	fork_id = fork();
	if (fork_id < 0)
		perror_exit("minishell", EXIT_FAILURE);
	if (fork_id == 0)
	{
		if (dup2(pipe_in, STDIN_FILENO) < 0)
			perror_exit("minishell", EXIT_FAILURE);
		close(pipe_in);
		exec_multiple_cmd(cmd);
	}
	close(pipe_in);
	return (fork_id);
}

