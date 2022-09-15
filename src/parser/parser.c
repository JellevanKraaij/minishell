#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

t_list	*parser(char *line)
{
	t_list		*tokens;
	t_list		*commands;

	if (line == NULL)
		return (NULL);
	tokens = null_exit(ft_lstnew(create_token(line, DEFAULT)));
	update_token_list(&tokens, lexer_process);
	update_token_list(&tokens, expand_vars);
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
