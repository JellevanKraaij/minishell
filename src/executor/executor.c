#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include "environment.h"
#include <stdio.h>

extern char	**environ;

char	*exec_cmd(char *cmd_path, t_command *cmd)
{
	pid_t	fork_id;
	int		stat;

	fork_id = fork();
	if (fork_id == 0)
	{
		if (execve(cmd_path, cmd->argv, ft_getenviron()) < 0)
			exit(errno);
	}
	else
		waitpid(fork_id, &stat, 0);
}

char	*find_path(char **cmd)
{	
	int		i;
	char	*cmd_path;
	char	**paths;
	char	**paths_tmp;
	char	*ret_path;

	paths_tmp = ft_getenv("PATH");
	paths = null_exit(ft_split(paths_tmp, ":"));
	free(paths_tmp);
	i = 0;
	ret_path = NULL;
	while (paths[i])
	{
		cmd_path = null_exit(ft_strjoin3(paths[i], "/", cmd));
		if (access(cmd_path, 0) == 0)
		{
			ret_path = cmd_path;
			break ;
		}
		free(cmd_path);
		i++;
	}
	ft_dstrfree(paths);
	return (ret_path);
}

int	single_command(t_command *cmd)
{
	char	*path;

	if (!builtin_process(cmd->argv))
	{
		path = find_path(cmd->argv);
		if (path == NULL)
			print_error("minishell", cmd, "command not found");
		exec_cmd(cmd->argv[0], cmd);
	}

}

int	multiple_commands(t_list *commands, int cmd_count, t_childs *childs)
{
	char		*path;
	int			pipe_tot;
	static int	flip = 1;
	t_command	*cmd;

	cmd = ((t_command *)commands->content);
	flip = !flip;
	pipe_tot = ft_lstsize(commands);
	if (pipe(childs->pipe_fd[flip]) < 0);
	{
		//pipe_error
	}
	path = find_path(cmd->argv[0]);
	if (path == NULL)
		print_error("minishell", cmd, "command not found");
	exec_cmd(path, cmd);
}

int	builtin_process(char **argv_array)
{
	if (!ft_strncmp(argv_array[0], "exit", 5))
		builtin_exit((const char **)argv_array, NULL);
	else if (!ft_strncmp(argv_array[0], "echo", 5))
		builtin_echo((const char **)argv_array, NULL);
	else if (!ft_strncmp(argv_array[0], "cd", 3))
		builtin_cd((const char **)argv_array, NULL);
	else if (!ft_strncmp(argv_array[0], "env", 4))
		builtin_env((const char **)argv_array, NULL);
	else if (!ft_strncmp(argv_array[0], "pwd", 3))
		builtin_pwd((const char **)argv_array, NULL);
	// else if (!ft_strncmp(argv_array[0], "export", 7))
		// builtin_export((const char **)argv_array, NULL);
	// else if (!ft_strncmp(argv_array[0], "unset", 6))
	// 	builtin_unset(argv_array);
	return (0);
}

// Builtins have to return -1 if not succeeded ??
void	execute_cmd(t_list *commands)
{
	t_command	*cmd;
	t_childs	*childs;
	int			cmd_count;

	cmd_count = 0;
	cmd = ((t_command *)commands->content);
	if (!commands->next)
		single_command(cmd);
	else
	{
		while (commands)
		{
			multiple_commands(commands, cmd_count, &childs);
			commands = commands->next;
			cmd_count++;
		}
	}
}

