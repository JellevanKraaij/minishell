#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include "environment.h"
#include <stdio.h>

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

void	execute_cmd(t_list *commands)
{
	t_command	*cmd;
	t_childs	childs;
	int			last_cmd;

	last_cmd = 0;
	cmd = ((t_command *)commands->content);
	if (!commands->next)
		single_command(cmd);
	else
	{
		childs.child_count = 0;
		while (commands)
		{
			multiple_commands(commands->content, &childs, last_cmd);
			commands = commands->next;
			if (!commands->next)
				last_cmd = 1;
			childs.child_count++;
		}
	}
}
