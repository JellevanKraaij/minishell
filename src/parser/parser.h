#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

# define WHITESPACE " "

typedef enum e_token
{
	END = 0,
	NORMAL,
	STRING_S = '\'',
	STRING_D = '\"',
}	t_token;

typedef struct s_line_data
{
	char	*line;
	t_token	*status;
}	t_line_data;

// add qoutes metadata to line and removes the unnecessary quotes 
t_line_data	*process_quotes(char *line);

// trim whitespaces defined under WHITESPACE
void		trim_whitespace(t_line_data *line);

t_line_data	*init_line_data(size_t length);
t_line_data	*destroy_line_data(t_line_data *metachar);

#endif