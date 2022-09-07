#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include "environment.h"
#include <stdio.h>
#include <sys/wait.h>

int	builtin_process(char **argv_array)
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

char	*find_path(char *cmd)
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

static int	wait_for_childs(int child_count, int last_pid)
{
	int	i;
	int	exit_code;
	int	status;

	i = 0;
	exit_code = 1;
	while (i < child_count)
	{
		if (waitpid(-1, &status, 0) == last_pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = WTERMSIG(status) + 128;
		}
		if (WIFEXITED(status) || WIFSIGNALED(status))
			i++;
	}
	return (exit_code);
}

int	execute_cmd(t_list *commands)
{
	t_command	*cmd;
	t_childs	childs;
	int			last_cmd;
	int			last_pid;
	int			ret_value;

	last_cmd = 0;
	cmd = ((t_command *)commands->content);
	if (!commands->next)
		ret_value = single_command(cmd);
	else
	{
		childs.child_count = 0;
		while (commands)
		{
			if (!commands->next)
				last_cmd = 1;
			last_pid = multiple_commands(commands->content, &childs, last_cmd);
			commands = commands->next;
			childs.child_count++;
		}
		ret_value = wait_for_childs(childs.child_count, last_pid);
	}
	return (ret_value);
}
