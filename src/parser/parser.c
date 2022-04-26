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
	printf("str = '%s' type = %d\n", token->str, token->type);
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
	update_token_list(&tokens, get_next_quote);
	ft_lstiter(tokens, fprint_tokens);
}
