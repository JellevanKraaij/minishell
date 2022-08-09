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

typedef enum e_fileflags
{
	INPUT = REDIR_INPUT,
	OUTPUT = REDIR_OUTPUT,
	OUTPUT_APP = REDIR_OUTPUT_APPEND
}	t_fileflags;

typedef struct s_file
{
	char		*name;
	t_fileflags	flag;
}	t_file;

typedef struct s_command
{
	t_list	*argv;
	t_list	*files;
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
int		is_token_type_redir(t_token token);

t_command *init_command(void);
t_command *destroy_command(t_command *cmd);

t_file *init_file(void);
t_file *destroy_file(t_file *file);
t_file *create_file(char *name, t_fileflags flag);

#endif