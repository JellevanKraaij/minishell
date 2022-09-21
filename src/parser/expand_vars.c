#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>

static int	check_amb_redir(t_token token, char *expanded, t_token prev)
{
	char	*tmp;

	if (!is_token_type_redir(prev) || token.type == DOUBLE_QUOTED)
		return (0);
	tmp = ft_strtrim(expanded, WHITESPACE);
	printf("tmp='%s'\n", tmp);
	if (ft_strlen(tmp) < 1 || ft_strchrset(tmp, WHITESPACE) != NULL)
	{
		print_error("minishell", token.str, "ambiguous redirect");
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
