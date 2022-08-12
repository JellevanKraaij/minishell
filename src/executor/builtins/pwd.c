#include "minishell.h"
#include "executor.h"
#include <libft.h>
#include <limits.h>
#include <stdio.h>

int	builtin_pwd(const char **argv, const char **envp)
{
	char	*wd;

	(void)argv;
	(void)envp;
	wd = null_exit(getcwd(NULL, 0));
	printf("%s\n", wd);
	free(wd);
}
