#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*line;

	init_signals();
	while (1)
	{
		line = readline(SHELL_PROMPT);
		parse_exec(line);
		if (*line)
			add_history(line);
		free(line);
	}
}
