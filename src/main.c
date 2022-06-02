#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


int	main(void)
{
	char		*line;

	// init_signals();
	while (1)
	{
		line = readline(SHELL_PROMPT);
		if (line == NULL)
			exit(1);
		// parse_exec(line);
		if (*line)
			add_history(line);
		free(line);
	}
}
