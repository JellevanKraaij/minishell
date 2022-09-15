#include "minishell.h"
#include "executor.h"
#include "environment.h"
#include <sys/stat.h>
#include <stdio.h>

void	check_executable(char *path)
{
	struct stat	statbuff;

	if (access(path, F_OK) < 0)
	{
		print_error("minishell", path, "No such file or directory");
		exit(127);
	}
	if (stat(path, &statbuff) < 0)
		perror_exit("minishell", 1);
	if (S_ISDIR(statbuff.st_mode))
	{
		print_error("minishell", path, "is a directory");
		exit(126);
	}
	if (access(path, X_OK) < 0)
	{
		print_error("minishell", path, "Permission denied");
		exit(126);
	}
}

char	*lookup_executable(char *cmd)
{
	char	*path;

	if (ft_strchr(cmd, '/') != NULL)
	{
		check_executable(cmd);
		return (cmd);
	}
	else
	{
		path = find_path(cmd);
		if (path == NULL)
			exit(127);
		if (access(path, X_OK) < 0)
		{
			print_error("minishell", "path", "Permission denied");
			exit(126);
		}
	}
	return (path);
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
	while (paths[i] && ft_strcmp(cmd, ".") && ft_strcmp(cmd, ".."))
	{
		cmd_path = null_exit(ft_strjoin3(paths[i], "/", cmd));
		if (access(cmd_path, F_OK) == 0)
		{
			ret_path = cmd_path;
			break ;
		}
		free(cmd_path);
		i++;
	}
	if (ret_path == NULL)
		print_error("minishell", cmd, "command not found");
	ft_dstrfree(paths);
	return (ret_path);
}
