#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libft.h>

void	sigint_h(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_h(int sig)
{
	(void)sig;
	ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

void	init_signals(void)
{
	signal(SIGINT, sigint_h);
	signal(SIGQUIT, sigquit_h);
}
