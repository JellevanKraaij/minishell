#include "minishell.h"
#include "parser.h"
#include "libft.h"

static ssize_t	strlen_quoted(const char *str, char c)
{
	char	*pntr;

	pntr = ft_strchr(str, c);
	if (pntr == NULL)
		return (-1);
	return (pntr - str);
}

static int	unclosed_quote(char *line, int i, t_token *token)
{
	int		current_pos;

	current_pos = i;
	while (line[i])
		i++;
	token->str = null_exit(ft_substr(line, current_pos + 1, i));
	return (i - current_pos);
}

int	tokenize_quoted(char *line, int i, t_token *token)
{
	char	temp_token;
	ssize_t	quote_length;

	temp_token = line[i];
	quote_length = strlen_quoted(&line[i + 1], temp_token);
	if (quote_length < 0 || !line[i + 1])
	{
		token->type = UNCLOSED;
		return (unclosed_quote(line, i, token));
	}
	if (temp_token == '\'')
		token->type = SINGLE_QUOTED;
	if (temp_token == '\"')
		token->type = DOUBLE_QUOTED;
	token->str = null_exit(ft_substr(line, i + 1, quote_length));
	return (quote_length + 2);
}
