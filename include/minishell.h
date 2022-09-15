#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include "parser.h"

# define SHELL_PROMPT "minishell> "
# define HEREDOC_PROMT "heredoc> "
# define REPRINT_PROMT 1
# define IGNORE_SIGNAL 0

extern int	g_last_exit_code;

//Errors
void	perror_exit(const char *s, int error_code) __attribute__((noreturn));
void	*null_exit(void	*ptr);
void	print_error(char *name, char *error_desc, char *error);
t_list	*parse_exec(char *line);
int		execute_cmd(t_list	*commands);
void	enable_signals(int print_promt);
void	disable_signals(void);

#endif
