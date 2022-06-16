#ifndef PARSER_H
# define PARSER_H

# include <libft.h>

# define WHITESPACE " "

typedef enum e_type
{
	DEFAULT,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	REDIR_INPUT,
	HEREDOC,
	REDIR_OUTPUT,
	REDIR_OUTPUT_APPEND,
	PIPE,
	UNCLOSED
}	t_type;

typedef struct s_token
{
	char	*str;
	t_type	type;
}	t_token;

typedef struct s_command
{
	char	*cmd;
	t_list	*args;
}	t_command;

// add qoutes metadata to line and removes the unnecessary quotes 
t_token	*lexer_process(t_token *input);
t_token	*expand_vars(t_token *input);
t_token	*split_tokens(t_token *input);

t_token	*init_token(void);
t_token	*destroy_token(t_token *token);
t_token	*create_token(char *str, size_t len, t_type type);
void	update_token_list(t_list **lst, t_token *(*token_f)(t_token *));
size_t	find_token_len(char *str, char *set);

t_list	*parse_tokens(t_list *tokens);
int		is_token_type_text(t_token token);

t_command *init_command(void);
t_command *destroy_command(t_command *cmd);


#endif