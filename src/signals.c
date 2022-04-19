#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	sigint_h(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	signal(SIGINT, sigint_h);
}
