/* ************************************************************************** */
/*									  */
/*							::::::::	  */
/*   minishell.h										:+: :+:	  */
/*						   +:+		  */
/*   By: jvan-kra <jvan-kra@student.codam.nl>	   +#+				*/
/*						   +#+					  */
/*   Created: 2022/03/30 23:41:24 by jvan-kra	 #+#  #+#			 */
/*   Updated: 2022/03/30 23:41:24 by jvan-kra	 ########   odam.nl	   */
/*									  */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_PROMPT "minishell$> "

# define WHITESPACE " "

typedef enum e_type
{
	WORD, //undefined
	SINGLE_QUOTED, // string single quotes
	DOUBLE_QUOTED, // string double quotes
	REDIR_INPUT, // <
	REDIR_OUTPUT, // >
	REDIR_OUTPUT_APPEND, //  >>
	HERE_DOC, //  <<
	PIPE, // |
	UNCLOSED,
	END
}	t_type;

typedef struct s_token
{
	char			*str;
	t_type			type;
}	t_token;

//Errors
void		perror_exit(const char *s, int error_code) __attribute__((noreturn));
void		*null_exit(void	*ptr);
void		print_error(char *name, char *error_desc, char *error);
void		parse_exec(char *line);
void		init_signals(void);
t_token		*create_token(t_token *input);
void		print_token(t_token *token);

#endif
