#include "minishell.h"
#include "executor.h"
#include "environment.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

static int	set_pwd(const char **argv)
{
	const char	*tmp_pwd;

	if (!getenv("PWD"))
	{
		tmp_pwd = getcwd(NULL, 0);
		if (tmp_pwd == NULL)
		{
			print_error("minishell", (char *)argv[0], "pwd not found");
			return (1);
		}
		ft_setenv("PWD", tmp_pwd, 1);
		free((char *)tmp_pwd);
	}
	tmp_pwd = getcwd(NULL, 0);
	if (tmp_pwd == NULL)
	{
		print_error("minishell", (char *)argv[0], "pwd not found");
		return (1);
	}
	ft_setenv("OLDPWD", tmp_pwd, 1);
	free((char *)tmp_pwd);
	return (0);
}

static int	set_oldpwd_cd(const char **argv)
{
	const char	*tmp;

	tmp = argv[1];
	if (!tmp)
		tmp = (getenv("HOME"));
	if (argv[1] && argv[1][0] == '-' && !argv[1][1])
	{
		tmp = (getenv("OLDPWD"));
		if (!tmp)
		{
			print_error("minishell", (char *)argv[0], "old pwd not set");
			return (1);
		}
	}
	if (chdir(tmp) < 0)
	{
		print_error("minishell", (char *)argv[0], strerror(errno));
		return (1);
	}
	return (0);
}

int	builtin_cd(const char **argv, const char **envp)
{
	(void)envp;
	if (ft_dstrlen((char **)argv) > 2)
	{
		print_error("minishell", (char *)argv[0], "too many arguments");
		return (1);
	}
	if (set_pwd(argv) || set_oldpwd_cd(argv))
		return (1);
	return (0);
}
