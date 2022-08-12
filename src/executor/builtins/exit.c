#include "minishell.h"
#include "executor.h"
#include <libft.h>
#include <stdlib.h>

int	builtin_exit(const char **argv, const char **envp)
{
	(void)envp;
	if (ft_dstrlen(argv) > 1)
		print_error("minishell", "exit", "too many arguments");
	exit(1);
}
