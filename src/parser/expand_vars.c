#include "minishell.h"
#include "parser.h"
#include "libft.h"

t_list	*expand_vars(t_list *tokens)
{
	t_token	*token;
	t_list	*ret;
	t_type	prev;

	ret = NULL;
	prev = DEFAULT;
	while (tokens)
	{
		token = tokens->content;
		if ((token->type == DEFAULT || token->type == DOUBLE_QUOTED) \
			&& prev != HEREDOC)
			ft_lstadd_back(&ret, null_exit(ft_lstnew(create_token(\
				expand_vars_string(token->str, token->type), token->type))));
		else
			ft_lstadd_back(&ret, null_exit(ft_lstnew(create_token(\
				token->str, token->type))));
		if (token->type != SEPERATOR)
			prev = token->type;
		tokens = tokens->next;
	}
	return (ret);
}
