/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_executable.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:13 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:13 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "environment.h"
#include <sys/stat.h>

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

	path = ft_getenv("PATH");
	if (ft_strchr(cmd, '/') != NULL || path == NULL || path[0] == '\0')
	{
		check_executable(cmd);
		return (cmd);
	}
	else
	{
		path = find_path(cmd);
		if (path == NULL)
		{
			print_error("minishell", cmd, "command not found");
			exit(127);
		}
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
	char	*ret_path;

	paths = null_exit(ft_split(ft_getenv("PATH"), ':'));
	i = 0;
	ret_path = NULL;
	if (cmd[0] != '\0' && ft_strcmp(cmd, ".") && ft_strcmp(cmd, ".."))
	{
		while (paths[i])
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
	}
	ft_dstrfree(paths);
	return (ret_path);
}
