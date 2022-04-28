#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>

static t_type	op_to_type(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(str, ">>", 2))
		return (OUT_REDIR_A);
	if (!ft_strncmp(str, "<", 1))
		return (IN_REDIR);
	if (!ft_strncmp(str, ">", 1))
		return (OUT_REDIR);
	if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	return (DEFAULT);
}

static size_t	calc_op_lenght(char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		return (2);
	else
		return (1);
}

t_token	*process_operators(t_token *input)
{
	static ssize_t	pos = 0;
	t_token			*token;
	size_t			op_pos;

	token = NULL;
	if (input->type != DEFAULT && pos == 0)
	{
		pos = -1;
		token = create_token(input->str, ft_strlen(input->str), input->type);
	}
	while (pos >= 0 && input->str[pos] != '\0')
	{
		op_pos = find_token_len(&input->str[pos], "<>|");
		if (op_pos == 0)
			op_pos = calc_op_lenght(&input->str[pos]);
		token = create_token(&input->str[pos], op_pos, \
		op_to_type(&input->str[pos]));
		pos += op_pos;
		if (token != NULL)
			break ;
	}
	if (token == NULL)
		pos = 0;
	return (token);
}
