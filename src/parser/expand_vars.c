#include "minishell.h"
#include "parser.h"
#include "libft.h"

void	lookup_var(char **var)
{
	char	*ret;

	if (!ft_strncmp(*var, "?", 2))
		ret = null_exit(ft_strdup("0"));
	else
	{
		ret = getenv(*var);
		if (ret == NULL)
			ret = null_exit(ft_strdup(""));
		else
			ret = null_exit(ft_strdup(ret));
	}
	free(*var);
	*var = ret;
}

size_t	calc_varlen(char *var)
{
	size_t	i;

	if (var[1] == '?')
		return (2);
	i = 1;
	while (ft_isalnum(var[i]) || var[i] == '_')
		i++;
	return (i);
}

void	replace_var(char **str, size_t start, size_t *len)
{
	char	*before;
	char	*var;
	char	*after;
	size_t	varlen;

	varlen = calc_varlen(&(*str)[start]);
	before = null_exit(ft_substr(*str, 0, start));
	var = null_exit(ft_substr(*str, start + 1, varlen - 1));
	after = null_exit(ft_strdup(&(*str)[start + varlen]));
	lookup_var(&var);
	free(*str);
	*str = ft_strjoin3(before, var, after);
	free(before);
	free(after);
	*len = ft_strlen(var);
	free(var);
}

t_token	*expand_vars(t_token *input)
{
	static int		start = 0;
	size_t			i;
	size_t			varlen;
	char			*str;

	if (start != 0)
	{
		start = 0;
		return (NULL);
	}
	start = 1;
	if (input->type != DEFAULT && input->type != STRING_D)
		return (create_token(input->str, ft_strlen(input->str), input->type));
	i = 0;
	str = input->str;
	while (input->str[i] != '\0')
	{
		if (input->str[i] == '$')
		{
			replace_var(&str, i, &varlen);
			i += varlen;
		}
		i++;
	}
	return (create_token(str, ft_strlen(str), input->type));
}
