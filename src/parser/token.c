#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>

t_token	*init_token(void)
{
	t_token	*ret;

	ret = null_exit(malloc(sizeof(t_token)));
	ret->str = NULL;
	return (ret);
}

t_token	*destroy_token(t_token *token)
{
	free(token->str);
	free(token);
	return (NULL);
}

t_token	*create_token(char *str, size_t len, t_type type)
{
	t_token	*token;

	token = init_token();
	token->type = type;
	if (type == DEFAULT)
		token->str = null_exit(ft_strntrim(str, WHITESPACE, len));
	else
		token->str = null_exit(ft_strndup(str, len));
	if (*token->str == '\0' && type != STRING_D && type != STRING_S)
	{
		printf("return empty\n");
		return (destroy_token(token));
	}
	return (token);
}

void	update_token_list(t_list **lst, t_token *(*token_f)(t_token *))
{
	t_list	*lst_i;
	t_list	*ret;
	t_token	*token;

	ret = NULL;
	lst_i = *lst;
	while (lst_i != NULL)
	{
		while (1)
		{
			token = (*token_f)(lst_i->content);
			if (token == NULL)
				break ;
			ft_lstadd_back(&ret, null_exit(ft_lstnew(token)));
		}
		lst_i = lst_i->next;
	}
	ft_lstclear(lst, (void (*)(void *))destroy_token);
	*lst = ret;
}
