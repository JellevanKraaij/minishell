#ifndef PARSER_H
# define PARSER_H

# include <libft.h>

# define WHITESPACE " "

typedef enum e_type
{
	DEFAULT,
	STRING_S,
	STRING_D
}	t_type;

typedef struct s_token
{
	char	*str;
	t_type	type;
}	t_token;

// add qoutes metadata to line and removes the unnecessary quotes 
t_token	*get_next_quote(char *line);

t_token	*init_token(void);
t_token	*destroy_token(t_token *token);

#endif