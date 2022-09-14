#include "minishell.h"
#include "environment.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	g_last_exit_code = 0;

void	set_shell_variables(char **argv)
{
	char	*shlvl;
	int		level_count;
	char	*temp_char;

	ft_setenv("SHELL", argv[0], 1);
	shlvl = ft_getenv("SHLVL");
	if (!shlvl)
	{
		ft_setenv("SHLVL", "1", 1);
		return ;
	}
	level_count = ft_atoi(shlvl);
	level_count ++;
	temp_char = null_exit(ft_itoa(level_count));
	ft_setenv("SHLVL", temp_char, 1);
	free(temp_char);
}

int	main(int argc, char **argv)
{
	char	*line;

	(void)argc;
	set_shell_variables(argv);
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
