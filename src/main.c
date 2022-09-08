#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*line;

	while (1)
	{
		enable_signals(REPRINT_PROMT);
		line = readline(SHELL_PROMPT);
		enable_signals(IGNORE_SIGNAL);
		parse_exec(line);
		if (*line)
			add_history(line);
		free(line);
	}
}
