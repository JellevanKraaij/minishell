#include "minishell.h"
#include "parser.h"
#include "libft.h"

static t_type	quote_to_type(char c)
{
	if (c == '\'')
		return (STRING_S);
	if (c == '\"')
		return (STRING_D);
	return (DEFAULT);
}

static size_t	calc_quote_lenght(char *str, char type)
{
	char	*tmp;

	tmp = ft_strchr(str, type);
	if (tmp == NULL)
	{
		print_error("minishell", "fatal", "unclosed quote");
		exit(1);
	}
	return (tmp - str);
}

t_token	*process_quotes(t_token *in)
{
	static size_t	pos = 0;
	t_token			*token;
	size_t			q_pos;
	size_t			len;

	token = NULL;
	while (in->str[pos] != '\0')
	{
		q_pos = find_token_len(&in->str[pos], "'\"");
		if (q_pos)
			token = create_token(&in->str[pos], q_pos, DEFAULT);
		else
		{
			len = calc_quote_lenght(&in->str[pos + 1], in->str[pos]);
			token = create_token(&in->str[pos + 1], len, \
			quote_to_type(in->str[pos]));
			q_pos = len + 2;
		}
		pos += q_pos;
		if (token != NULL)
			break ;
	}
	if (token == NULL)
		pos = 0;
	return (token);
}
