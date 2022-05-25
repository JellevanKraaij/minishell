#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


void	parse_exec(char *line)
{
	t_tokenized	tokenized;

	tokenized.token = WORD;
	while (tokenized.token != END)
	{
		tokenized = create_token(line);
		print_tokenized(tokenized);
	}
}
