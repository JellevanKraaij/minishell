#include "minishell.h"
#include "environment.h"
#include "parser.h"
#include "libft.h"

static void	lookup_var(char **var)
{
	char	*ret;

	if (!ft_strncmp(*var, "?", 2))
		ret = null_exit(ft_itoa(g_last_exit_code));
	else
	{
		ret = ft_getenv(*var);
		if (ret == NULL)
			ret = null_exit(ft_strdup(""));
		else
			ret = null_exit(ft_strdup(ret));
	}
	free(*var);
	*var = ret;
}

static size_t	calc_varlen(char *var)
{
	size_t	i;

	if (var[0] == '~')
		return (1);
	if (var[1] == '?')
		return (2);
	i = 1;
	while (ft_isalnum(var[i]) || var[i] == '_')
		i++;
	return (i);
}

static void	replace_var(char **str, size_t start, size_t *len)
{
	char	*before;
	char	*var;
	char	*after;
	size_t	varlen;

	varlen = calc_varlen(&(*str)[start]);
	before = null_exit(ft_substr(*str, 0, start));
	if (*str[0] == '~')
		var = ft_strdup("HOME");
	else
		var = null_exit(ft_substr(*str, start + 1, varlen - 1));
	after = null_exit(ft_strdup(&(*str)[start + varlen]));
	lookup_var(&var);
	free(*str);
	*str = null_exit(ft_strjoin3(before, var, after));
	free(before);
	free(after);
	*len = ft_strlen(var);
	free(var);
}

static	int	var_is_valid_first(int c)
{
	if (c == '?' || c == '_' || ft_isalpha(c))
		return (1);
	return (0);
}

char	*expand_vars_string(char *input, t_type type)
{
	size_t	i;
	size_t	varlen;
	char	*ret;

	i = 0;
	ret = null_exit(ft_strdup(input));
	while (ret[i] != '\0')
	{
		if ((ret[i] == '$' && var_is_valid_first(ret[i + 1])) \
		|| (ret[i] == '~' && type == DEFAULT))
		{
			replace_var(&ret, i, &varlen);
			i += varlen;
		}
		else
			i++;
	}
	return (ret);
}