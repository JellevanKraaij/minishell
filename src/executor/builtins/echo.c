/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga           <jvan-kra/to      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:43:54 by jvan-kra/     #+#    #+#                 */
/*   Updated: 2022/10/04 17:43:54 by jvan-kra/     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <libft.h>

static int	ft_isn(const char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_echo(const char **argv, const char **envp)
{
	int	i;
	int	flag_n;

	flag_n = 0;
	i = 1;
	(void)envp;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0 && ft_isn(argv[i]) == 0)
	{
		flag_n = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd((char *)argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!flag_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
