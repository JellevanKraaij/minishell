#include "minishell.h"
#include "executor.h"
#include "environment.h"
#include "libft.h"
#include <stdio.h>

int	arr_count(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**sort_list(char **envp)
{
	int		count;
	int		i;
	int		j;
	char	*tmp;

	tmp = NULL;
	count = arr_count(envp);
	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

static int	print_exp(const char **envp)
{
	size_t	idx;
	char	*name;
	char	*value;
	char	*loc;
	int		i;

	i = 0;
	while (envp[i])
	{
		loc = ft_strchr(envp[i], '=');
		if (!loc)
			printf("declare -x %s\n", envp[i]);
		else
		{
			idx = loc - envp[i];
			name = ft_strndup(envp[i], idx);
			value = ft_strdup(&envp[i][idx + 1]);
			printf("declare -x %s=\"%s\"\n", name, value);
			free(name);
			free(value);
		}
		i++;
	}
	return (0);
}

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
		return (print_exp(envp));
	export_multiple_arg(argv);
	return (0);
}
