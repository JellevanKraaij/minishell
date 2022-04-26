#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	parse_exec(char *line)
{
	t_token	*token;

	if (line == NULL)
	{
		rl_clear_history();
		exit(0);
	}
	if (*line == '\0')
		return ;
	while ((token = get_next_quote(line)))
	{
		printf("type = %d, str = '%s'\n", token->type, token->str);
	}
}
