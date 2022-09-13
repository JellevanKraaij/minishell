#include "minishell.h"
#include "executor.h"
#include "environment.h"

int	builtin_unset(const char **argv, const char **envp)
{
	(void)envp;
	if (ft_dstrlen((char **)argv) > 2)
	{
		print_error("minishell", (char *)argv[0], "too many arguments");
		return (1);
	}
	if (argv[1])
	{
		if (isvalid_key((char *)argv[1]))
		{
			print_error("minishell: export", (char *)argv[1], \
						"not a valid identifier");
			return (1);
		}
		ft_unsetenv(argv[1]);
	}
	return (0);
}
