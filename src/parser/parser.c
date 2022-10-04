/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:40 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:40 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * @brief create abstract syntax list from user input
 *
 * @param line input
 * @return t_list* abstract syntax list
 */
t_list	*parser(char *line)
{
	t_list		*tokens;
	t_list		*commands;

	if (line == NULL)
		return (NULL);
	tokens = null_exit(ft_lstnew(create_token(line, DEFAULT)));
	update_token_list(&tokens, lexer_process);
	repalce_token_list(&tokens, expand_vars);
	repalce_token_list(&tokens, split_tokens);
	repalce_token_list(&tokens, combine_tokens);
	if (BUILD_DEBUG)
		print_tokens(tokens);
	commands = parse_tokens(tokens);
	ft_lstclear(&tokens, ((void (*))(void *)destroy_token));
	if (commands == NULL)
		return (NULL);
	if (BUILD_DEBUG)
		print_commands(commands);
	return (commands);
}
