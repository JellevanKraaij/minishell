#include "minishell.h"
#include "executor.h"
#include "environment.h"

int	builtin_unset(const char **argv, const char **envp)
{
	size_t	i;
	size_t	ret;

	i = 1;
	(void)envp;
	ret = 0;
	while (argv[i])
	{
		if (isvalid_key((char *)argv[i]))
		{
			print_error("minishell: unset", (char *)argv[i], \
						"not a valid identifier");
			ret = 1;
		}
		else
			ft_unsetenv(argv[i]);
		i++;
	}
	return (ret);
}
