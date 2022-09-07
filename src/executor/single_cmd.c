#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include "environment.h"
#include <stdio.h>
#include <sys/wait.h>

static int	exec_single_cmd(t_command *cmd)
{
	pid_t	fork_id;
	int		status;
	char	*path;

	fork_id = fork();
	if (fork_id < 0)
		perror_exit("minishell", EXIT_FAILURE);
	if (fork_id == 0)
	{
		path = find_path(cmd->argv[0]);
		if (path == NULL)
		{
			print_error("minishell", cmd->argv[0], "command not found");
			exit(127);
		}
		ft_lstiter(cmd->files, open_dup_file);
		if (execve(path, cmd->argv, ft_getenviron()) < 0)
			perror_exit("minishell", EXIT_FAILURE);
	}
	else
	{
		while (1)
		{
			waitpid(fork_id, &status, 0);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				return (WTERMSIG(status) + 128);
		}
	}
	return (0);
}

int	single_command(t_command *cmd)
{
	int		ret_value;

	ret_value = builtin_process(cmd->argv);
	if (ret_value < 0)
	{
		ret_value = exec_single_cmd(cmd);
	}
	return (ret_value);
}
