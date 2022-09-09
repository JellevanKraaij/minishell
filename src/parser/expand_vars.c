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
		ret = null_exit(ft_strdup(ft_getenv(*var)));
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

t_token	*expand_vars(t_token *input)
{
	static int		start = 0;
	size_t			i;
	size_t			varlen;

	if (start != 0)
	{
		start = 0;
		return (NULL);
	}
	start = 1;
	if (input->type != DEFAULT && input->type != DOUBLE_QUOTED)
		return (create_token(input->str, input->type));
	i = 0;
	while (input->str[i] != '\0')
	{
		if ((input->str[i] == '$' && var_is_valid_first(input->str[i + 1])) \
		|| (input->str[i] == '~' && input->type == DEFAULT))
		{
			replace_var(&input->str, i, &varlen);
			i += varlen;
		}
		else
			i++;
	}
	return (create_token(input->str, input->type));
}
