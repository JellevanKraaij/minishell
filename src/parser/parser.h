#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

# define WHITESPACE " "

typedef enum e_token
{
	END = 0,
	NORMAL,
	VAR,
	STRING_S = '\'',
	STRING_D = '\"',
}	t_token;

typedef struct s_line_data
{
	char	*line;
	t_token	*token;
}	t_line_data;

typedef struct s_cmd_data
{
	t_line_data	*cmd;
	t_line_data	*infile;
	t_line_data	*outfile;
}	t_cmd_data;

// add qoutes metadata to line and removes the unnecessary quotes 
t_line_data	*process_quotes(char *line);

// trim whitespaces defined under WHITESPACE
void		trim_whitespace(t_line_data *line);

t_line_data	*init_line_data(size_t length);
t_line_data	*destroy_line_data(t_line_data *linedata);

t_cmd_data	*init_cmd_data(size_t length);
t_cmd_data	*destroy_cmd_data(t_cmd_data *cmddata);

#endif