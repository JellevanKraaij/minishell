#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include "environment.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int	is_path(char *path)
{
	return (ft_strchr(path, '/') != NULL);
}

int	check_executable(char *path)
{
	struct stat	statbuff;

	if (stat(path, &statbuff) < 0)
		perror_exit("minishell", 1);
	if (S_ISDIR(statbuff.st_mode))
	{
		print_error("minishell", path, "is a directory");
		exit(-1);
	}
	if (access(path, X_OK) < 0)
	{
		print_error("minishell", path, "Permission denied");
		return (-1);
	}
	return (0);
}

char	*lookup_executable(char *cmd)
{
	char	*path;

	if (is_path(cmd))
	{
		path = cmd;
		if (check_executable(path) < 0)
			exit(126);
	}
	else
	{
		path = find_path(cmd);
		if (path == NULL)
			exit(127);
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
	if (ret_path == NULL)
		print_error("minishell", cmd, "command not found");
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
