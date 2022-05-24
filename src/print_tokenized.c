#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*get_type(int token)
{
	char	*types[] = {"WORD", "SINGLE_QUOTED", "DOUBLE_QUOTED", "REDIR_INPUT", "REDIR_OUTPUT", \
	"REDIR_OUTPUT_APPEND", "HERE_DOC", "PIPE", "END", "UNCLOSED"};

	return (types[token]);
}

void	print_tokenized(t_tokenized tokenized)
{
	printf("Token num : '%i'\n", tokenized.token);
	printf("Token type: '%s'\n", get_type(tokenized.token));
	printf("String    : '%s'\n\n", tokenized.element);
}
