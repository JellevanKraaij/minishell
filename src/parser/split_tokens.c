#include "minishell.h"
#include "parser.h"
#include "libft.h"

t_token	*split_tokens(t_token *input)
{
	static size_t	pos = 0;
	static int		done = 0;
	char			**parts;
	t_token			*ret;

	if (done == 1)
	{
		done = 0;
		return (NULL);
	}
	if (input->type != DEFAULT)
	{
		done = 1;
		return (create_token(input->str, ft_strlen(input->str), input->type));
	}
	parts = null_exit(ft_splitset(input->str, WHITESPACE));
	if (parts[pos] == NULL)
	{
		pos = 0;
		return (NULL);
	}
	ret = create_token(parts[pos], ft_strlen(parts[pos]), DEFAULT);
	ft_split_free(parts);
	pos++;
	return (ret);
}
