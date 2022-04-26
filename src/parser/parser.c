#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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
	update_token_list(&tokens, process_quote);
	update_token_list(&tokens, process_operators);
	ft_lstiter(tokens, fprint_tokens);
}
