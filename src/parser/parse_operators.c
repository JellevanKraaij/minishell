#include "minishell.h"
#include "parser.h"
#include "libft.h"

void parse_redirects(t_line_data **infile, t_line_data **outfile)
{
	
}

void	parse_operators(t_line_data *line)
{
	t_cmd_data	*tmp;
	t_list		*ret;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;

	while (line->line[i])
	{
		if (line->line[i] ==)
		{
			parse_redirects()
		}
		if (line->line[i] == '|' && line->token[i] == NORMAL)
		{
		}
		i++;
	}
}
