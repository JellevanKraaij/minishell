#ifndef PARSER_H
# define PARSER_H

# include <libft.h>

# define WHITESPACE " "

typedef enum e_type
{
	DEFAULT,
	STRING_S,
	STRING_D,
	IN_REDIR,
	HEREDOC,
	OUT_REDIR,
	OUT_REDIR_A,
	PIPE,
}	t_type;

typedef struct s_token
{
	char	*str;
	t_type	type;
}	t_token;

// add qoutes metadata to line and removes the unnecessary quotes 
t_token	*process_quotes(t_token *input);
t_token	*process_operators(t_token *input);
t_token	*expand_vars(t_token *input);

t_token	*init_token(void);
t_token	*destroy_token(t_token *token);
t_token	*create_token(char *str, size_t len, t_type type);
void	update_token_list(t_list **lst, t_token *(*token_f)(t_token *));
size_t	find_token_len(char *str, char *set);

#endif