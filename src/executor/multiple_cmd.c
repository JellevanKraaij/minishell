#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>

static void	exec_multiple_cmd(char *cmd_path, t_command *cmd)
{

	printf("path: %s\n and cmd: %s\n", cmd_path, cmd->argv[0]);
}

int	multiple_commands(t_command *cmd, t_childs *childs, int last_cmd)
{
	char		*path;
	static int	flip = 1;
	pid_t		fork_id;

	flip = !flip;
	if (!last_cmd)
	{
		if (pipe(childs->pipe_fd[flip]) < 0)
		{
			//pipe_error
			printf("ERRROORRRRR\n");
		}
	}
	path = find_path(cmd->argv[0]);
	if (path == NULL)
		print_error("minishell", cmd->argv[0], "command not found");
	fork_id = fork();
	if (fork_id == 0)
	{
		ft_lstiter(cmd->files, open_dup_file);
		exec_multiple_cmd(path, cmd);
	}
	if (!last_cmd)
		close(childs->pipe_fd[flip][PIPE_OUT_WRITE]);
	if (childs->child_count != 0)
		close(childs->pipe_fd[!flip][PIPE_IN_READ]);
	return (0);
}
