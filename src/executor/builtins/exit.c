#include "minishell.h"
#include "executor.h"
#include <libft.h>
#include <stdio.h>

static int	str_isnum(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(const char **argv, const char **envp)
{
	(void)envp;
	printf("exit\n");
	if (ft_dstrlen((char **)argv) == 1)
		exit(0);
	if (!str_isnum(argv[1]))
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
	exit(ft_atoi(argv[1]));
}
