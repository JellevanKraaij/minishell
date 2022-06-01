#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static t_token	*init_token(void)
{
	t_token	*ret;

	ret = null_exit(malloc(sizeof(t_token)));
	ret->str = NULL;
	ret->type = WORD;
	return (ret);
}

void	parse_exec(char *line)
{
	t_token	*token;

	token = init_token();
	while (token->type != END)
	{
		token = create_token(line);
		print_token(token);
	}
}
