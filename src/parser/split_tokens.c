#include "minishell.h"
#include "parser.h"
#include "libft.h"

t_token	*split_tokens(t_token *input)
{
	static size_t	pos = 0;
	t_token			*ret;
	size_t			loc;

	if (input->str[pos] == '\0')
	{
		pos = 0;
		return (NULL);
	}
	if (input->type != DEFAULT)
	{
		pos = ft_strlen(input->str);
		return (create_token(input->str, pos, input->type));
	}
	loc = (size_t)ft_strchrset(&input->str[pos], WHITESPACE);
	if (loc == 0)
	{
		ret = create_token(&input->str[pos], ft_strlen(&input->str[pos]), input->type);
		pos += ft_strlen(&input->str[pos]);
		return (ret);
	}
	loc = loc - (size_t) & input->str[pos];
	ret = create_token(&input->str[pos], loc, input->type);
	pos += loc + 1;
	return (ret);
}
