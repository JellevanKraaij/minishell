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

typedef enum e_token_labels
{
	WORD, //undefined
	SINGLE_QUOTED, // string single quotes
	DOUBLE_QUOTED, // string double quotes
	REDIR_INPUT, // <
	REDIR_OUTPUT, // >
	REDIR_OUTPUT_APPEND, //  >>
	HERE_DOC, //  <<
	PIPE, // |
	END,
	UNCLOSED
}	t_token_labels;

typedef struct s_tokenized
{
	t_token_labels	token;
	char			*element;
}	t_tokenized;

//Errors
void		perror_exit(const char *s, int error_code) __attribute__((noreturn));
void		*null_exit(void	*ptr);
void		print_error(char *name, char *error_desc, char *error);
void		parse_exec(char *line);
void		init_signals(void);
t_tokenized	create_token(char *line);
void		print_tokenized(t_tokenized tokenized);

#endif
