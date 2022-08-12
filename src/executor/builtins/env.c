#include "minishell.h"
#include "executor.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern char	**environ;

int	builtin_env(const char **argv, const char **envp)
{
	size_t	i;

	i = 0;
	(void)envp;
	if (ft_dstrlen(argv) > 1)
	{
		print_error("minishell", "env", "too many arguments");
		return ;
	}
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
