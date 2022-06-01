#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*get_type(int token)
{
	char	*types[] = {"WORD", "SINGLE_QUOTED", "DOUBLE_QUOTED", "REDIR_INPUT", "REDIR_OUTPUT", \
	"REDIR_OUTPUT_APPEND", "HERE_DOC", "PIPE", "UNCLOSED", "END"};

	return (types[token]);
}

void	print_token(t_token *token)
{
	printf("Token num : '%i'\n", token->type);
	printf("Token type: '%s'\n", get_type(token->type));
	printf("String    : '%s'\n\n", token->str);
}
