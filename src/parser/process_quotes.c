#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>

static t_type	char_to_type(char c)
{
	if (c == '\'')
		return (STRING_S);
	if (c == '\"')
		return (STRING_D);
	return (DEFAULT);
}

static size_t	first_quote(char *str)
{
	char	*s_quote;
	char	*d_quote;

	s_quote = ft_strchr(str, '\'');
	d_quote = ft_strchr(str, '\"');
	if (s_quote == NULL && d_quote == NULL)
		return (ft_strlen(str));
	if (s_quote == NULL || s_quote > d_quote)
		return (d_quote - str);
	else
		return (s_quote - str);
}

static size_t	calc_quote_lenght(char *str, char type)
{
	char	*tmp;

	tmp = ft_strchr(str, type);
	if (tmp == NULL)
		return (ft_strlen(str));
	if (tmp - str == 0)
		return (0);
	return (tmp - str);
}

t_token	*get_next_quote(t_token *input)
{
	static size_t	pos = 0;
	t_token			*token;
	size_t			quote_pos;
	size_t			len;

	token = NULL;
	while (input->str[pos] != '\0')
	{
		quote_pos = first_quote(&input->str[pos]);
		if (quote_pos)
			token = create_token(&input->str[pos], quote_pos, DEFAULT);
		else
		{
			len = calc_quote_lenght(&input->str[pos + 1], input->str[pos]);
			token = create_token(&input->str[pos + 1], len, \
			char_to_type(input->str[pos]));
			quote_pos = len + 2;
		}
		pos += quote_pos;
		if (token != NULL)
			break ;
	}
	if (token == NULL)
		pos = 0;
	return (token);
}
