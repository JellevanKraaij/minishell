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
	SEPERATOR,
	UNCLOSED
}	t_type;

typedef struct s_token
{
	char	*str;
	t_type	type;
}	t_token;

typedef enum e_fileflags
{
	INVALID = -1,
	INPUT,
	INPUT_HEREDOC,
	INPUT_HEREDOC_LIT,
	OUTPUT,
	OUTPUT_APP
}	t_fileflags;

typedef struct s_file
{
	char		*name;
	t_fileflags	flag;
}	t_file;

typedef struct s_command
{
	char	**argv;
	t_list	*files;
}	t_command;

// lexer & parser functions
t_token		*lexer_process(t_token *input);
t_token		*expand_vars(t_token *input);
t_list		*split_tokens(t_list *tokens);
t_list		*combine_tokens(t_list *tokens);
t_list		*parse_tokens(t_list *tokens);

//token helpers
t_token		*init_token(void);
t_token		*destroy_token(t_token *token);
t_token		*create_token(char *str, t_type type);
void		update_token_list(t_list **lst, t_token *(*token_f)(t_token *));
void		repalce_token_list(t_list **lst, t_list *(*list_f)(t_list *));
size_t		find_token_len(char *str, char *set);
int			is_token_type_text(t_token token);
int			is_token_type_redir(t_token token);
t_fileflags	token_to_fileflag(t_token token);

//command helpers
t_command	*init_command(void);
t_command	*destroy_command(t_command *cmd);
void		clear_command(t_command *cmd);

//file helpers
t_file		*init_tfile(void);
t_file		*destroy_tfile(t_file *file);
t_file		*create_tfile(char *name, t_fileflags flag);

//debug print functions
void		print_tokens(t_list *tokens);
void		print_commands(t_list *commands);

#endif