#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_PROMPT "minishell$> "
//Errors
void	perror_exit(const char *s, int error_code) __attribute__((noreturn));
void	*null_exit(void	*ptr);
void	print_error(char *name, char *error_desc, char *error);
void	parse_exec(char *line);
void	init_signals(void);

#endif
