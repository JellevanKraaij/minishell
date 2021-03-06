#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>

static int	ft_isspace(int i)
{
	if (!i)
		return (0);
	if (ft_strchr(WHITESPACE, i))
		return (1);
	return (0);
}

static ssize_t	strlen_quoted(const char *str, char c)
{
	char	*pntr;

	pntr = ft_strchr(str, c);
	if (pntr == NULL)
		return (-1);
	return (pntr - str);
}

static size_t	fill_token(t_type label, const char *sym, \
				t_token *token)
{
	token->type = label;
	token->str = null_exit(ft_strdup(sym));
	return (ft_strlen(sym));
}

static size_t	tokenize_sym(char *line, int i, t_token *token)
{
	if (line[i] == '>' && line[i + 1] == '>')
		return (fill_token(REDIR_OUTPUT_APPEND, ">>", token));
	if (line[i] == '<' && line[i + 1] == '<')
		return (fill_token(REDIR_OUTPUT_APPEND, "<<", token));
	if (line[i] == '<')
		return (fill_token(REDIR_INPUT, "<", token));
	if (line[i] == '>')
		return (fill_token(REDIR_OUTPUT, ">", token));
	if (line[i] == '|')
		return (fill_token(PIPE, "|", token));
	return (0);
}

static int	unclosed_quote(char *line, int i, t_token *token)
{	
	int		current_pos;

	if (!line[i + 1])
	{
		token->str = NULL;
		return (1);
	}
	current_pos = i;
	while (line[i])
		i++;
	token->str = null_exit(ft_substr(line, current_pos + 1, i));
	return (i - current_pos);
}

static int	tokenize_quoted(char *line, int i, t_token *token)
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

static int	tokenize_word(char *line, int i, t_token *token)
{
	int	start;

	start = i;
	token->type = DEFAULT;
	while (line[i] && !ft_strchr("<>|\'\"", line[i]) \
			&& !ft_strchr(WHITESPACE, line[i]))
		i++;
	token->str = null_exit(ft_substr(&line[start], 0, i - start));
	return (i);
}

t_token	*lexer_process(t_token *input)
{
	t_token		*token;
	static int	i = 0;

	token = init_token();
	while (ft_isspace(input->str[i]))
		i++;
	if (input->str[i] == '\'' || input->str[i] == '\"')
		i = i + tokenize_quoted(input->str, i, token);
	else if (input->str[i] == '<' || input->str[i] == '>' \
			|| input->str[i] == '|')
		i = i + tokenize_sym(input->str, i, token);
	else if (input->str[i])
		i = tokenize_word(input->str, i, token);
	else
	{
		free(token);
		i = 0;
		return (NULL);
	}
	return (token);
}
