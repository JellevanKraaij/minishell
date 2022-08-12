#include "minishell.h"
#include "executor.h"

int	builtin_unset(const char **argv, const char **envp)
{
	(void)envp;
	if (ft_dstrlen(argv) > 2)
	{
		print_error("minishell", "export", "too many arguments");
		return ;
	}
}
