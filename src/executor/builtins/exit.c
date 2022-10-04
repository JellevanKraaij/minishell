/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga           <jvan-kra/to      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:43:58 by jvan-kra/     #+#    #+#                 */
/*   Updated: 2022/10/04 17:43:58 by jvan-kra/     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <libft.h>
#include <limits.h>
#include <stdio.h>
#include <readline/readline.h>

static int	parse_exit_num(const char *str, long *number)
{
	int				sign;
	unsigned long	ret;

	ret = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		ret = (ret * 10) + (*str - '0');
		if ((ret > LONG_MAX && sign == 1) || \
		ret > ((unsigned long)LONG_MAX + 1))
			return (-1);
		str++;
	}
	ret *= sign;
	if (*str != '\0')
		return (-1);
	*number = ret;
	return (0);
}

int	builtin_exit(const char **argv, const char **envp)
{
	long	num;

	(void)envp;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (ft_dstrlen((char **)argv) == 1)
		exit(g_last_exit_code);
	if (parse_exit_num(argv[1], &num) < 0)
	{
		print_error("minishell", (char *)argv[0], \
					"numeric argument required");
		rl_clear_history();
		exit(255);
	}
	else if (ft_dstrlen((char **)argv) > 2)
	{
		print_error("minishell", (char *)argv[0], "too many arguments");
		return (1);
	}
	exit(num);
}
