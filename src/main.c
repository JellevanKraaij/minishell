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

/**
 * @brief display promt and read line input
 * 
 * @param prompt 
 * @return char* return line in case of input, return NULL 
 * 			in case of empty intput.
 */
char	*read_prompt(char *prompt)
{
	char	*line;

	enable_signals(REPRINT_PROMT);
	line = readline(prompt);
	enable_signals(IGNORE_SIGNAL);
	if (line == NULL)
	{
		rl_clear_history();
		ft_putendl_fd("exit", STDERR_FILENO);
		exit (g_last_exit_code);
	}
	if (*line == '\0')
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	return (line);
}

int	main(int argc, char **argv)
{
	char	*line;
	t_list	*commands;

	(void)argc;
	rl_outstream = stderr;
	set_shell_variables(argv);
	while (1)
	{
		line = read_prompt(SHELL_PROMPT);
		commands = parser(line);
		free(line);
		execute_commands(commands);
		ft_lstclear(&commands, (void (*))(void *)destroy_command);
	}
}
