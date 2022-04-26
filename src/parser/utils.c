#include "minishell.h"
#include "parser.h"
#include <libft.h>

size_t	find_token_len(char *str, char *set)
{
	char	*pos;

	pos = ft_strrchrset(str, set);
	if (pos == NULL)
		return (ft_strlen(str));
	return (pos - str);
}
