#include "minishell.h"
#include "executor.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

void	builtin_cd(const char **argv, const char **envp)
{
	const char	*tmp;

	(void)envp;
	if (ft_dstrlen(argv) > 2)
	{
		print_error("minishell", "cd", "too many arguments");
		return ;
	}
	tmp = argv[1];
	if (!tmp)
		tmp = (getenv("HOME"));
	if (chdir(tmp) < 0)
	{
		print_error("minishell", "cd", strerror(errno));
		return ;
	}
}