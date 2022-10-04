#include "minishell.h"
#include "executor.h"
#include "libft.h"

#define BASH_VAR_ESCAPE_CHARS "\"\\$"

static void	sort_list(char **envp)
{
	int		count;
	int		i;
	int		j;
	char	*tmp;

	tmp = NULL;
	count = ft_dstrlen(envp);
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
}

static char	*add_slash(char *value)
{
	size_t	i;
	char	*start;
	char	*end;

	i = 0;
	while (value[i])
	{
		if (ft_strchr(BASH_VAR_ESCAPE_CHARS, value[i]))
		{
			if (i == 0)
				value = null_exit(ft_strjoin("\\", value));
			else
			{
				start = null_exit(ft_strndup(value, i));
				end = null_exit(ft_strdup(&value[i]));
				free(value);
				value = null_exit(ft_strjoin3(start, "\\", end));
				free(start);
				free(end);
			}
			i++;
		}
		i++;
	}
	return (value);
}

static void	write_exp(size_t i, char *loc, char **envp)
{
	size_t	idx;
	char	*name;
	char	*value;

	idx = loc - envp[i];
	name = null_exit(ft_strndup(envp[i], idx));
	value = null_exit(ft_strdup(&envp[i][idx + 1]));
	value = add_slash(value);
	ft_putstr_fd(name, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	ft_putstr_fd(value, STDOUT_FILENO);
	ft_putendl_fd("\"", STDOUT_FILENO);
	free(name);
	free(value);
}

int	print_exp(char **envp)
{
	char	*loc;
	size_t	i;

	i = 0;
	envp = null_exit(ft_dstrdup(envp));
	sort_list(envp);
	while (envp[i])
	{
		loc = ft_strchr(envp[i], '=');
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (!loc)
			ft_putendl_fd((char *)envp[i], STDOUT_FILENO);
		else
			write_exp(i, loc, envp);
		i++;
	}
	ft_dstrfree(envp);
	return (0);
}
