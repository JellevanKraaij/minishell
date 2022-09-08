#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>

# define SHELL_PROMPT "minishell$> "
# define REPRINT_PROMT 1
# define IGNORE_SIGNAL 0

//Errors
void	perror_exit(const char *s, int error_code) __attribute__((noreturn));
void	*null_exit(void	*ptr);
void	print_error(char *name, char *error_desc, char *error);
void	parse_exec(char *line);
int		execute_cmd(t_list	*commands);
void	enable_signals(int print_promt);
void	disabler_signals(void);

#endif
