#include "minishell.h"
#include "parser.h"
#include <stdlib.h>

t_line_data	*init_line_data(size_t length)
{
	t_line_data	*res;

	res = null_exit(malloc(sizeof(t_line_data)));
	res->status = null_exit(malloc(sizeof(t_token) * length));
	res->line = null_exit(malloc(sizeof(char) * length));
	return (res);
}

t_line_data	*destroy_line_data(t_line_data *metachar)
{
	free(metachar->status);
	free(metachar->line);
	free(metachar);
	return (NULL);
}
