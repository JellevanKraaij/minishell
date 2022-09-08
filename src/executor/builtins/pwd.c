#include "minishell.h"
#include "executor.h"
#include "environment.h"
#include <libft.h>
#include <stdio.h>

int	builtin_pwd(const char **argv, const char **envp)
{
	char	*wd;

	(void)argv;
	(void)envp;
	wd = getcwd(NULL, 0);
	if (wd == NULL)
	{
		wd = ft_getenv("PWD");
		if (wd == NULL)
		{
			print_error("minishell", (char *)argv[0], "pwd not found");
			return (1);
		}
		printf("%s\n", wd);
		return (0);
	}
	printf("%s\n", wd);
	free(wd);
	return (0);
}
