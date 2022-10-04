/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga           <jvan-kra/to      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:43 by jvan-kra/     #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:43 by jvan-kra/     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"

static void	split_default(t_list **lst, char *str)
{
	size_t	i;
	char	**split;

	i = 0;
	split = null_exit(ft_splitset(str, WHITESPACE));
	if (split[0] == NULL)
	{
		ft_split_free(split);
		return ;
	}
	while (split[i])
	{
		ft_lstadd_back(lst, null_exit(\
		ft_lstnew(create_token(split[i], DEFAULT))));
		if (split[i + 1])
			ft_lstadd_back(lst, null_exit(\
			ft_lstnew(create_token(" ", SEPERATOR))));
		i++;
	}
	ft_split_free(split);
}

/**
 * @brief split default tokens on spaces
 *
 * @param tokens list
 * @return t_list* updated token list
 */
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
