#include "minishell.h"
#include "executor.h"
#include <libft.h>
#include <stdio.h>
#include <limits.h>

int	parse_exit_num(const char *str, long *number)
{
	unsigned long	ret;

	ret = 0;
	while (ft_isdigit(*str))
	{
		ret = (ret * 10) + (*str - '0');
		if (ret > LONG_MAX)
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	*number = (long)ret;
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
		print_error("minishell: exit", (char *)argv[0], \
					"numeric argument required");
		return (255);
	}
	else if (ft_dstrlen((char **)argv) > 2)
	{
		print_error("minishell", (char *)argv[0], "too many arguments");
		return (1);
	}
	exit(num);
}
