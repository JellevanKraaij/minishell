/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_vars.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:34 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:34 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>

//in case of empty or invalid redirect name print error
static int	check_amb_redir(t_token token, char *expanded, t_token prev)
{
	char	*tmp;

	if (!is_token_type_redir(prev) || token.type == DOUBLE_QUOTED)
		return (0);
	tmp = null_exit(ft_strtrim(expanded, WHITESPACE));
	if (ft_strlen(tmp) < 1 || ft_strchrset(tmp, WHITESPACE) != NULL)
	{
		print_error("minishell", token.str, "ambiguous redirect");
		g_last_exit_code = 1;
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

static t_list	*create_token_node(char *str, t_type type)
{
	return (null_exit(ft_lstnew(create_token(str, type))));
}

static int	is_expand(t_type type, t_type prev)
{
	return ((type == DEFAULT || type == DOUBLE_QUOTED) && prev != HEREDOC);
}

/**
 * @brief expands variables in DEFAULT or DOUBLE_QUOTED
 * 			and in other cases ignores
 *
 * @param tokens list to expand
 * @return t_list* list of expanded tokens
 */

t_list	*expand_vars(t_list *tokens)
{
	t_token	*token;
	t_list	*ret;
	t_token	prev;
	char	*tmp;

	ret = NULL;
	prev.type = DEFAULT;
	while (tokens)
	{
		token = tokens->content;
		if (is_expand(token->type, prev.type))
		{
			tmp = expand_vars_string(token->str, token->type);
			if (check_amb_redir(*token, tmp, prev))
				return (NULL);
			ft_lstadd_back(&ret, create_token_node(tmp, token->type));
			free(tmp);
		}
		else
			ft_lstadd_back(&ret, create_token_node(token->str, token->type));
		if (token->type != SEPERATOR)
			prev = *token;
		tokens = tokens->next;
	}
	return (ret);
}
