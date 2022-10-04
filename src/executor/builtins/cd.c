/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga           <jvan-kra/to      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:43:52 by jvan-kra/     #+#    #+#                 */
/*   Updated: 2022/10/04 17:43:52 by jvan-kra/     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "environment.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

static char	*parse_arg(const char **argv)
{
	char	*chdir_path;

	if (!argv[1])
	{
		chdir_path = ft_getenv("HOME");
		if (!chdir_path)
			print_error("minishell", (char *)argv[0], "HOME not set");
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		chdir_path = ft_getenv("OLDPWD");
		if (!chdir_path)
			print_error("minishell", (char *)argv[0], "old pwd not set");
	}
	else
		chdir_path = (char *)argv[1];
	return (chdir_path);
}

static int	exec_cd(const char **argv)
{
	char	*chdir_path;
	char	*old_pwd;

	chdir_path = parse_arg(argv);
	if (!chdir_path)
		return (1);
	if (chdir(chdir_path) < 0)
	{
		print_error("minishell", (char *)argv[0], strerror(errno));
		return (1);
	}
	old_pwd = ft_getenv("PWD");
	if (old_pwd)
		ft_setenv("OLDPWD", old_pwd, 1);
	else
		ft_unsetenv("OLDPWD");
	chdir_path = getcwd(NULL, 0);
	ft_setenv("PWD", chdir_path, 1);
	free(chdir_path);
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
	if (exec_cd(argv))
		return (1);
	return (0);
}
