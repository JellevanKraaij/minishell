#include "minishell.h"
#include "parser.h"
#include "libft.h"

void	trim_whitespace(t_line_data *line)
{
	size_t		i;
	size_t		j;
	int			current;
	int			next;

	i = 0;
	j = 0;
	current = (ft_strchr(WHITESPACE, line->line[i]) == NULL);
	while (line->line[i])
	{
		if (line->line[i + 1])
			next = (ft_strchr(WHITESPACE, line->line[i + 1]) == NULL);
		else
			next = 0;
		if (line->status[i] != NORMAL || current || next)
		{
			line->line[j] = line->line[i];
			line->status[j] = line->status[i];
			j++;
		}
		i++;
		current = next;
	}
	line->line[j] = '\0';
	line->status[j] = END;
}
