#include "minishell.h"
#include "executor.h"

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

static void	print_exp(const char **envp)
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
}

void	builtin_export(const char **argv, const char **envp)
{
	(void)envp;
	if (ft_dstrlen(argv) > 2)
	{
		print_error("minishell", "export", "too many arguments");
		return ;
	}
}
