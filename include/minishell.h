/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:45:19 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:45:19 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include "parser.h"

# ifndef BUILD_DEBUG
#  define BUILD_DEBUG 0
# else
#  define BUILD_DEBUG 1
# endif

# define SHELL_PROMPT "minishell> "
# define HEREDOC_PROMT "heredoc> "
# define REPRINT_PROMT 1
# define IGNORE_SIGNAL 0

extern int	g_last_exit_code;

//Errors
void	perror_exit(const char *s, int error_code) __attribute__((noreturn));
void	*null_exit(void	*ptr);
void	print_error(char *name, char *error_desc, char *error);
t_list	*parser(char *line);
void	execute_commands(t_list	*commands);
void	enable_signals(int print_promt);
void	disable_signals(void);

#endif
