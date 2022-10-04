/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:44:36 by jvan-kra/     #+  #+#    #+#             */
/*   Updated: 2022/10/04 19:32:35 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"

static int	ft_isspace(int i)
{
	if (!i)
		return (0);
	if (ft_strchr(WHITESPACE, i))
		return (1);
	return (0);
}

static int	tokenize_word(char *line, int i, t_token *token)
{
	int	start;

	start = i;
	token->type = DEFAULT;
	while (line[i] && !ft_strchr("<>|\'\"", line[i]) \
			&& !ft_strchr(WHITESPACE, line[i]))
		i++;
	token->str = null_exit(ft_substr(&line[start], 0, i - start));
	return (i);
}

static int	tokenize_space(char *line, int i, t_token *token)
{
	token->type = SEPERATOR;
	token->str = null_exit(ft_strdup(" "));
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

t_token	*lexer_process(t_token *input)
{
	t_token		*token;
	static int	i = 0;

	token = init_token();
	if (ft_isspace(input->str[i]))
		i = tokenize_space(input->str, i, token);
	else if (input->str[i] == '\'' || input->str[i] == '\"')
		i = i + tokenize_quoted(input->str, i, token);
	else if (input->str[i] == '<' || input->str[i] == '>' \
			|| input->str[i] == '|')
		i = i + tokenize_sym(input->str, i, token);
	else if (input->str[i])
		i = tokenize_word(input->str, i, token);
	else
	{
		free(token);
		i = 0;
		return (NULL);
	}
	return (token);
}
