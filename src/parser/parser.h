#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

# define WHITESPACE " "

typedef enum e_quote_stat
{
	END = 0,
	NORMAL,
	STRING_S = '\'',
	STRING_D = '\"',
}	t_quote_stat;

typedef struct s_line_meta
{
	char			*line;
	t_quote_stat	*status;
}	t_line_meta;

// add qoutes metadata to line and removes the unnecessary quotes 
t_line_meta	*process_quotes(char *line);

// trim whitespaces defined under WHITESPACE
void		trim_whitespace(t_line_meta *line);

t_line_meta	*init_meta_char(size_t length);
t_line_meta	*destroy_meta_char(t_line_meta *metachar);

#endif