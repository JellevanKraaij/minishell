#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	parse_exec(char *line)
{
	t_line_data	*line_s;

	if (line == NULL)
	{
		rl_clear_history();
		exit(0);
	}
	if (*line == '\0')
		return ;
	line_s = process_quotes(line);
	if (line_s == NULL)
		return ;
	trim_whitespace(line_s);
	printf("line = \"%s\"\n", line_s->line);
	if (ft_strncmp(line_s->line, "exit", 4) == 0)
		exit (0);
	print_error("minishell", "command not found", line_s->line);
	destroy_line_data(line_s);
}
