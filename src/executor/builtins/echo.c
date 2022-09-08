#include "minishell.h"
#include "executor.h"
#include <libft.h>
#include <stdio.h>

int	builtin_echo(const char **argv, const char **envp)
{
	int	i;
	int	flag_n;

	flag_n = 0;
	i = 1;
	(void)envp;
	while (argv[i] && !ft_strcmp(argv[i], "-n"))
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
