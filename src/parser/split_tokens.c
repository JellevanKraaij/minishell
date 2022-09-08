#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>

static void	split_default(t_list **lst, char *str)
{
	size_t	i;
	char	**split;

	i = 0;
	split = null_exit(ft_splitset(str, WHITESPACE));
	if (split[0] == NULL)
		return ;
	while (split[i])
	{
		printf("split='%s'\n", split[i]);
		ft_lstadd_back(lst, null_exit(\
		ft_lstnew(create_token(split[i], DEFAULT))));
		if (split[i + 1])
			ft_lstadd_back(lst, null_exit(\
			ft_lstnew(create_token("", SEPERATOR))));
		i++;
	}
}

t_list	*split_tokens(t_list *tokens)
{
	t_list	*ret;
	t_token	*token;

	ret = NULL;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == DEFAULT)
			split_default(&ret, token->str);
		else
			ft_lstadd_back(&ret, null_exit(\
				ft_lstnew(create_token(token->str, token->type))));
		tokens = tokens->next;
	}
	return (ret);
}
