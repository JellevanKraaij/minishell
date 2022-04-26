#include "minishell.h"
#include "parser.h"
#include "libft.h"

t_token	*init_token(void)
{
	t_token	*ret;

	ret = null_exit(malloc(sizeof(t_token)));
	ret->str = NULL;
	return (ret);
}

t_token	*destroy_token(t_token *token)
{
	free(token->str);
	free(token);
	return (NULL);
}
