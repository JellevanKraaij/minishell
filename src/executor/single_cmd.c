#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include "environment.h"
#include <stdio.h>

extern char	**environ;

static void	exec_single_cmd(char *cmd_path, t_command *cmd)
{
	pid_t	fork_id;
	int		stat;

	fork_id = fork();
	if (fork_id == 0)
	{
		ft_lstiter(cmd->files, open_dup_file);
		if (execve(cmd_path, cmd->argv, ft_getenviron()) < 0)
			exit(0);
	}
	else
		waitpid(fork_id, &stat, 0);
}

int	single_command(t_command *cmd)
{
	char	*path;

	if (builtin_process(cmd->argv) < 0)
	{
		path = find_path(cmd->argv[0]);
		if (path == NULL)
			print_error("minishell", cmd->argv[0], "command not found");
		exec_single_cmd(path, cmd);
	}
	return (0);
}
