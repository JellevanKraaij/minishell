#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include "environment.h"
#include <stdio.h>

extern char	**environ;

static int	builtin_process(char **argv_array)
{
	if (!ft_strncmp(argv_array[0], "exit", 5))
		return ((!builtin_exit((const char **)argv_array, NULL)));
	if (!ft_strncmp(argv_array[0], "echo", 5))
		return (builtin_echo((const char **)argv_array, NULL));
	else if (!ft_strncmp(argv_array[0], "cd", 3))
		return (builtin_cd((const char **)argv_array, NULL));
	else if (!ft_strncmp(argv_array[0], "env", 4))
		return (builtin_env((const char **)argv_array, NULL));
	else if (!ft_strncmp(argv_array[0], "pwd", 3))
		return (builtin_pwd((const char **)argv_array, NULL));
	else if (!ft_strncmp(argv_array[0], "export", 7))
		return (builtin_export((const char **)argv_array, \
		(const char **)ft_getenviron()));
	else if (!ft_strncmp(argv_array[0], "unset", 6))
		return (builtin_unset((const char **)argv_array, \
		(const char **)ft_getenviron()));
	return (-1);
}

static char	*find_path(char *cmd)
{	
	int		i;
	char	*cmd_path;
	char	**paths;
	char	*paths_tmp;
	char	*ret_path;

	paths_tmp = ft_getenv("PATH");
	paths = null_exit(ft_split(paths_tmp, ':'));
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

static void	exec_cmd(char *cmd_path, t_command *cmd)
{
	pid_t	fork_id;
	int		stat;

	fork_id = fork();
	if (fork_id == 0)
	{
		if (execve(cmd_path, cmd->argv, ft_getenviron()) < 0)
			exit(0);
	}
	else
		waitpid(fork_id, &stat, 0);
}

static int	single_command(t_command *cmd)
{
	char	*path;

	if (builtin_process(cmd->argv) < 0)
	{
		printf("this is not a builtin\n");
		path = find_path(cmd->argv[0]);
		if (path == NULL)
			print_error("minishell", cmd->argv[0], "command not found");
		exec_cmd(path, cmd);
	}
	return (0);
}

static int	multiple_commands(t_list *commands, t_childs *childs)
{
	char		*path;
	int			pipe_tot;
	static int	flip = 1;
	t_command	*cmd;

	cmd = ((t_command *)commands->content);
	flip = !flip;
	pipe_tot = ft_lstsize(commands);
	if (pipe(childs->pipe_fd[flip]) < 0)
	{
		//pipe_error
		printf("ERRROORRRRR\n");
	}
	path = find_path(cmd->argv[0]);
	if (path == NULL)
		print_error("minishell", cmd->argv[0], "command not found");
	exec_cmd(path, cmd);
	return (0);
}

void	execute_cmd(t_list *commands)
{
	t_command	*cmd;
	t_childs	childs;

	cmd = ((t_command *)commands->content);
	if (!commands->next)
		single_command(cmd);
	else
	{
		printf("more cmds\n");
		childs.child_count = 0;
		while (commands)
		{
			multiple_commands(commands, &childs);
			commands = commands->next;
			childs.child_count++;
		}
	}
}
