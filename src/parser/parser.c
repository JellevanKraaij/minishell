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
	[STRING_S] = "STRING_S",
	[STRING_D] = "STRING_D",
	[IN_REDIR] = "IN_REDIR",
	[HEREDOC] = "HEREDOC",
	[OUT_REDIR] = "OUT_REDIR",
	[OUT_REDIR_A] = "OUT_REDIR_A",
	[PIPE] = "PIPE",
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
	update_token_list(&tokens, process_quotes);
	update_token_list(&tokens, process_operators);
	update_token_list(&tokens, expand_vars);
	update_token_list(&tokens, split_tokens);
	ft_lstiter(tokens, fprint_tokens);
}
