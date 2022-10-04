/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga           <jvan-kra/to      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:54 by jvan-kra/     #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:54 by jvan-kra/     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	if (token.type == DEFAULT || token.type == SINGLE_QUOTED || \
	token.type == DOUBLE_QUOTED)
		return (1);
	return (0);
}

int	is_token_type_redir(t_token token)
{
	if (token.type == REDIR_INPUT || token.type == REDIR_OUTPUT || \
	token.type == REDIR_OUTPUT_APPEND || token.type == HEREDOC)
		return (1);
	return (0);
}

t_fileflags	token_to_fileflag(t_token token)
{
	if (token.type == REDIR_INPUT)
		return (INPUT);
	if (token.type == REDIR_OUTPUT)
		return (OUTPUT);
	if (token.type == REDIR_OUTPUT_APPEND)
		return (OUTPUT_APP);
	if (token.type == HEREDOC)
		return (INPUT_HEREDOC);
	return (-1);
}
