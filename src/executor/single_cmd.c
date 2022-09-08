#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include "environment.h"
#include <stdio.h>

static int	exec_single_cmd(t_command *cmd)
{
	pid_t	fork_id;
	char	*path;

	fork_id = fork();
	if (fork_id < 0)
		perror_exit("minishell", EXIT_FAILURE);
	if (fork_id == 0)
	{
		ft_lstiter(cmd->files, open_dup_file);
		path = find_path(cmd->argv[0]);
		if (path == NULL)
		{
			print_error("minishell", cmd->argv[0], "command not found");
			exit(127);
		}
		if (execve(path, cmd->argv, ft_getenviron()) < 0)
			perror_exit("minishell", EXIT_FAILURE);
	}
	return (fork_id);
}

static void	backup_fds(int *backup_fd)
{
	backup_fd[STDIN_FILENO] = dup(STDIN_FILENO);
	backup_fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (backup_fd[STDIN_FILENO] < 0 || backup_fd[STDOUT_FILENO] < 0)
		perror_exit("minishell", 1);
}

static void	restore_fds(int *backup_fd)
{
	if (dup2(backup_fd[STDIN_FILENO], STDIN_FILENO) < 0 || \
			dup2(backup_fd[STDOUT_FILENO], STDOUT_FILENO) < 0)
		perror_exit("minishell", 1);
}

int	single_command(t_command *cmd)
{
	pid_t		child_pid;
	t_builtin_f	builtin_function;
	int			backup_fd[2];
	int			ret;

	builtin_function = lookup_builtin(cmd->argv[0]);
	if (builtin_function != NULL)
	{
		backup_fds(backup_fd);
		ft_lstiter(cmd->files, open_dup_file);
		ret = execute_builtin(cmd, builtin_function);
		restore_fds(backup_fd);
		return (ret);
	}
	child_pid = exec_single_cmd(cmd);
	return (wait_for_childs(1, child_pid));
}
