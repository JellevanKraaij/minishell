#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	parse_exec(char *line)
{
	if (line == NULL)
	{
		rl_clear_history();
		exit(0);
	}
	if (*line == '\0')
		return ;
	if (ft_strncmp(line, "exit", 4) == 0)
		exit (0);
	print_error("minishell", "command not found", line);
}
