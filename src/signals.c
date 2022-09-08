#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libft.h>

// handler for SIGQUIT signal (CTRL-C)
// creates new prompt on next line
static void	sigint_handler(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	enable_signals(int print_promt)
{
	if (print_promt)
		signal(SIGINT, sigint_handler);
	else
		signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	disabler_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
