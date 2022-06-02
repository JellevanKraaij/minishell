#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	parse_exec(t_token input)
{
	t_token	*token;

	while (1)
	{
		token = create_token(&input);
		if (!token)
			break ;
		print_token(token);
	}
}
