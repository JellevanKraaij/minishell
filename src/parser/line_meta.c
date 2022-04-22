#include "minishell.h"
#include "parser.h"
#include <stdlib.h>

t_line_meta	*init_meta_char(size_t length)
{
	t_line_meta	*res;

	res = null_exit(malloc(sizeof(t_line_meta)));
	res->status = null_exit(malloc(sizeof(t_quote_stat) * length));
	res->line = null_exit(malloc(sizeof(char) * length));
	return (res);
}

t_line_meta	*destroy_meta_char(t_line_meta *metachar)
{
	free(metachar->status);
	free(metachar->line);
	free(metachar);
	return (NULL);
}
