#include "minishell.h"
#include "executor.h"
#include <libft.h>
#include <stdio.h>

static int	ft_isn(const char *str)
{
	int	i;

	i = 0;
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
	while (argv[i] && argv[i][0] == '-' && ft_isn(&argv[i][1]) == 0)
	{
		flag_n = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!flag_n)
		printf("\n");
	return (0);
}
