#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

const char	*type_to_string(t_type type)
{
	const char	*type_str[] = {
	[DEFAULT] = "DEFAULT",
	[SINGLE_QUOTED] = "SINGLE_QUOTED",
	[DOUBLE_QUOTED] = "DOUBLE_QUOTED",
	[REDIR_INPUT] = "REDIR_INPUT",
	[HEREDOC] = "HEREDOC",
	[REDIR_OUTPUT] = "REDIR_OUTPUT",
	[REDIR_OUTPUT_APPEND] = "REDIR_OUTPUT_APPEND",
	[PIPE] = "PIPE",
	[UNCLOSED] = "UNCLOSED QUOTE",
	};

	return (type_str[type]);
}

void	fprint_tokens(void *data)
{
	t_token	*token;

	token = data;
	printf("type = %-12s | str = '%s'\n", \
	type_to_string(token->type), token->str);
}

void	parse_exec(char *line)
{
	t_list	*tokens;

	if (line == NULL)
	{
		rl_clear_history();
		exit(0);
	}
	if (*line == '\0')
		return ;
	tokens = null_exit(ft_lstnew(create_token(line, ft_strlen(line), DEFAULT)));
	update_token_list(&tokens, lexer_process);
	update_token_list(&tokens, expand_vars);
	update_token_list(&tokens, split_tokens);
	ft_lstiter(tokens, fprint_tokens);
}
