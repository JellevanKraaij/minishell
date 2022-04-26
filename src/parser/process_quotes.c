#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>

t_type	char_to_type(char c)
{
	if (c == '\'')
		return (STRING_S);
	if (c == '\"')
		return (STRING_D);
	return (DEFAULT);
}

size_t	first_quote(char *str)
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

size_t	calc_quote_lenght(char *str, char type)
{
	char	*tmp;

	tmp = ft_strchr(str, type);
	if (tmp == NULL)
		return (ft_strlen(str));
	if (tmp - str == 0)
		return (0);
	return (tmp - str);
}

t_token	*create_token(char *str, size_t len, t_type type)
{
	t_token	*token;

	if (len == 0)
		return (NULL);
	token = init_token();
	token->type = type;
	if (type == DEFAULT)
		token->str = null_exit(ft_strntrim(str, WHITESPACE, len));
	else
		token->str = null_exit(ft_strndup(str, len));
	if (*token->str == '\0')
		return (destroy_token(token));
	return (token);
}

t_token	*get_next_quote(char *line)
{
	static size_t	pos = 0;
	t_token			*token;
	size_t			quote_pos;
	size_t			len;

	token = NULL;
	while (line[pos] != '\0')
	{
		quote_pos = first_quote(&line[pos]);
		if (quote_pos)
			token = create_token(&line[pos], quote_pos, DEFAULT);
		else
		{
			len = calc_quote_lenght(&line[pos + 1], line[pos]);
			token = create_token(&line[pos + 1], len, char_to_type(line[pos]));
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
