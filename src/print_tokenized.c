#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*get_type(int token)
{
	char	*types[] = {"WORD", "SQUOTED", "DQUOTED", "RED_INPUT", "RED_OUTPUT", \
	"RED_OUT_APPEND", "RED_IN", "PIPE", "END"};

	return (types[token]);
}

void	print_tokenized(t_tokenized tokenized)
{
	printf("Token num : %i\n", tokenized.token);
	printf("Token type: %s\n", get_type(tokenized.token));
	printf("String    : %s\n\n", tokenized.element);
}
