#include "minishell.h"
#include "parser.h"
#include "libft.h"

// t_line_data	*expand_string(t_line_data *line, size_t *pos)
// {
// 	size_t	i;

// 	i = pos;
// 	while (line->line[i])
// }

// t_line_data	*expand_vars(t_line_data *line)
// {
// 	size_t	i;

// 	i = 0;
// 	while (line->line[i])
// 	{
// 		if (line->line[i] == '$' && line->token[i] == NORMAL || line->token == STRING_D)
// 		{
// 			line = expand_string(line, i);
// 		}
// 	}
// }
