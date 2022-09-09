#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include "environment.h"
#include <sys/wait.h>

static const t_builtin	g_builtins[] = {
{.name = "exit", .function = builtin_exit},
{.name = "echo", .function = builtin_echo},
{.name = "cd", .function = builtin_cd},
{.name = "env", .function = builtin_env},
{.name = "pwd", .function = builtin_pwd},
{.name = "export", .function = builtin_export},
{.name = "unset", .function = builtin_unset}
};

t_builtin_f	lookup_builtin(char *cmd)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_builtins) / sizeof(t_builtin))
	{
		if (ft_strcmp(cmd, g_builtins[i].name) == 0)
			return (g_builtins[i].function);
		i++;
	}
	return (NULL);
}

int	execute_builtin(t_command *cmd, t_builtin_f builtin_function)
{
	return (builtin_function((const char **)cmd->argv, \
		(const char **)ft_getenviron()));
}

char	*find_path(char *cmd)
{	
	int		i;
	char	*cmd_path;
	char	**paths;
	char	*paths_tmp;
	char	*ret_path;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (null_exit(ft_strdup(cmd)));
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

int	wait_for_childs(int child_count, int last_pid)
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
	t_childs	childs;
	size_t		cmd_count;
	int			last_cmd;
	int			last_pid;
	int			ret_value;

	last_cmd = 0;
	cmd_count = ft_lstsize(commands);
	if (cmd_count == 1)
		ret_value = single_command(commands->content);
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
