#include "minishell.h"
#include "executor.h"
#include <libft.h>
#include <stdlib.h>

int	builtin_exit(const char **argv, const char **envp)
{
	(void)envp;
	if (ft_dstrlen((char **)argv) > 1)
		print_error("minishell", (char *)argv[0], "too many arguments");
	exit(1);
}
