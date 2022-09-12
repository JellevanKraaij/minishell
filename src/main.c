#include "minishell.h"
#include "environment.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	g_last_exit_code = 0;

int	main(int argc, char **argv)
{
	char	*line;

	(void)argc;
	ft_setenv("SHELL", argv[0], 1);
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
