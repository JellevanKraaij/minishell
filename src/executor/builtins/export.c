#include "minishell.h"
#include "executor.h"
#include "environment.h"
#include "libft.h"
#include <stdio.h>


int	print_exp(char **envp);

static int	export_multiple_arg(const char **argv)
{
	char	*name;
	char	*value;
	char	*index_p;
	size_t	index;

	index_p = ft_strchr(argv[1], '=');
	if (index_p == NULL)
	{
		if (isvalid_key((char *)argv[1]))
		{
			print_error("minishell: export", (char *)argv[1], \
				"not a valid identifier");
			return (1);
		}
		ft_setenv(argv[1], NULL, 0);
		return (0);
	}
	index = index_p - argv[1];
	name = null_exit(ft_strndup(argv[1], index));
	if (isvalid_key(name))
	{
		print_error("minishell: export", (char *)argv[1], \
					"not a valid identifier");
		free(name);
		return (1);
	}
	value = null_exit(ft_strdup(&argv[1][index + 1]));
	ft_setenv(name, value, 1);
	free(name);
	free(value);
	return (0);
}

int	builtin_export(const char **argv, const char **envp)
{
	size_t		len;

	(void)envp;
	len = ft_dstrlen((char **)argv);
	if (len > 2)
	{
		print_error("minishell", (char *)argv[0], "too many arguments");
		return (1);
	}
	if (len == 1)
		return (print_exp((char **)ft_getenviron()));
	return (export_multiple_arg(argv));
}
