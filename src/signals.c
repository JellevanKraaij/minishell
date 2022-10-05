/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:45:02 by jvan-kra      #+  #+#    #+#             */
/*   Updated: 2022/10/05 16:59:44 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_last_exit_code = 1;
}

static void	sigint_incmd_handler(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDERR_FILENO);
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	enable_signals(int print_promt)
{
	if (print_promt)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, sigint_incmd_handler);
		signal(SIGQUIT, sigquit_handler);
	}
}

void	disable_signals(void)
{
	rl_catch_signals = 1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
