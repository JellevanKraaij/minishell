#include "minishell.h"
#include "parser.h"
#include <libft.h>

size_t	find_token_len(char *str, char *set)
{
	char	*pos;

	pos = ft_strchrset(str, set);
	if (pos == NULL)
		return (ft_strlen(str));
	return (pos - str);
}

int	is_token_type_text(t_token token)
{
	if (token.type == DEFAULT || token.type == SINGLE_QUOTED || token.type == DOUBLE_QUOTED)
		return (1);
	return (0);
}

int	is_token_type_redir(t_token token)
{
	if (token.type == REDIR_INPUT || token.type == REDIR_OUTPUT || token.type == REDIR_OUTPUT_APPEND)
		return (1);
	return (0);
}