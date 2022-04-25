#include "minishell.h"
#include "parser.h"
#include <stdlib.h>

// t_cmd_data	*init_cmd_data(size_t length)
// {
// 	t_cmd_data	*res;

// 	res = null_exit(malloc(sizeof(t_cmd_data)));
// 	res->token = null_exit(malloc(sizeof(t_token) * length));
// 	res->line = null_exit(malloc(sizeof(char) * length));
// 	res->stdin = NULL;
// 	res->outfile = NULL;
// 	return (res);
// }

// t_cmd_data	*destroy_cmd_data(t_cmd_data *cmddata)
// {
// 	free(cmddata->token);
// 	free(cmddata->line);
// 	free(cmddata->stdin);
// 	free(cmddata->outfile);
// 	free(cmddata);
// 	return (NULL);
// }
