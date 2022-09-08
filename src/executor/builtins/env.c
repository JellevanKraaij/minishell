#include "minishell.h"
#include "executor.h"
#include <stdio.h>

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
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
