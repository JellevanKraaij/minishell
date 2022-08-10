#include "minishell.h"
#include "executor.h"
#include <libft.h>
#include <stdio.h>

void	builtin_echo(const char **argv, const char **envp)
{
	int	i;
	int	flag_n;

	flag_n = 0;
	i = 1;
	(void)envp;
	if (argv[1] && !ft_strncmp(argv[1], "-n", 3))
	{
		i++;
		flag_n = 1;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
	}
	if (!flag_n)
		printf("\n");
}
