/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:43:56 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:43:56 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "libft.h"

int	builtin_env(const char **argv, const char **envp)
{
	size_t	i;

	i = 0;
	if (ft_dstrlen((char **)argv) > 1)
	{
		print_error("minishell", (char *)argv[0], "too many arguments");
		return (1);
	}
	while (envp[i])
	{
		ft_putendl_fd((char *)envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
