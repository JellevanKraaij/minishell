#include "minishell.h"
#include "parser.h"
#include <libft.h>

static	t_token	*to_token(t_list *node)
{
	if (node == NULL)
		return (NULL);
	return (node->content);
}

static char	*combine_strf(char *str1, char *str2)
{
	char	*ret;

	if (str1 == NULL)
		return (null_exit(ft_strdup(str2)));
	ret = null_exit(ft_strjoin(str1, str2));
	free(str1);
	return (ret);
}

static t_token	*try_combine(t_list **tokens)
{
	char	*combine;
	t_type	type;
	t_token	*ret;

	combine = NULL;
	type = DEFAULT;
	while (*tokens && is_token_type_text(*to_token(*tokens)))
	{
		combine = combine_strf(combine, to_token(*tokens)->str);
		if (to_token(*tokens)->type == DOUBLE_QUOTED || \
			to_token(*tokens)->type == SINGLE_QUOTED)
		{
			type = to_token(*tokens)->type;
		}
		*tokens = (*tokens)->next;
	}
	ret = create_token(combine, type);
	free(combine);
	return (ret);
}

t_list	*combine_tokens(t_list *tokens)
{
	t_list	*ret;

	ret = NULL;
	while (tokens)
	{
		if (is_token_type_text(*to_token(tokens)))
			ft_lstadd_back(&ret, null_exit(ft_lstnew(try_combine(&tokens))));
		else if (!is_token_type_text(*to_token(tokens)) \
		&& to_token(tokens)->type != SEPERATOR)
		{
			ft_lstadd_back(&ret, null_exit(ft_lstnew(\
			create_token(to_token(tokens)->str, to_token(tokens)->type))));
			tokens = tokens->next;
		}
		else
			tokens = tokens->next;
	}
	return (ret);
}
