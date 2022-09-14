#include "minishell.h"
#include "executor.h"
#include "environment.h"
#include "libft.h"
#include <stdio.h>


int	print_exp(char **envp);

static void	export_multiple_arg(const char **argv)
{
	char	*name;
	char	*value;
	char	*index_p;
	size_t	index;

	index_p = ft_strchr(argv[1], '=');
	if (index_p == NULL)
	{
		ft_setenv(argv[1], NULL, 0);
		return ;
	}
	index = index_p - argv[1];
	name = ft_strndup(argv[1], index);
	if (isvalid_key(name))
	{
		print_error("minishell: export", (char *)argv[1], \
					"not a valid identifier");
		free(name);
		return ;
	}
	value = ft_strdup(&argv[1][index + 1]);
	ft_setenv(name, value, 1);
	free(name);
	free(value);
}

int	builtin_export(const char **argv, const char **envp)
{
	size_t	len;

	len = ft_dstrlen((char **)argv);
	if (len > 2)
	{
		print_error("minishell", (char *)argv[0], "too many arguments");
		return (1);
	}
	if (len == 1)
		return (print_exp((char **)envp));
	export_multiple_arg(argv);
	return (0);
}
