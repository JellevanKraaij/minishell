/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:04 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:04 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "environment.h"
#include <libft.h>

int	builtin_pwd(const char **argv, const char **envp)
{
	char	*wd;

	(void)argv;
	(void)envp;
	wd = getcwd(NULL, 0);
	if (wd == NULL)
	{
		wd = ft_getenv("PWD");
		if (wd == NULL)
		{
			print_error("minishell", (char *)argv[0], "pwd not found");
			return (1);
		}
		ft_putendl_fd(wd, STDOUT_FILENO);
		return (0);
	}
	ft_putendl_fd(wd, STDOUT_FILENO);
	free(wd);
	return (0);
}
