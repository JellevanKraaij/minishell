#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// static int	ft_isspace(int i)
// {
// 	if (i == ' ' || i == '\t' || i == '\v' || i == '\f' || i == '\r')
// 		return (1);
// 	return (0);
// }

static ssize_t	get_index(const char *str, char c)
{
	char	*pntr;

	pntr = ft_strchr(str, c);
	if (pntr == NULL)
		return (-1);
	return (pntr - str);
}

static int	get_sym(char *line, int i, t_tokenized *tokenized)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		tokenized->token = OUTFILE_APPEND;
		tokenized->element = null_exit(ft_strdup(">>"));
		return (2);
	}
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		tokenized->token = HERE_DOC;
		tokenized->element = null_exit(ft_strdup("<<"));
		return (2);
	}
	else if (line[i] == '<')
	{
		tokenized->token = REDIR_INPUT;
		tokenized->element = null_exit(ft_strdup("<"));
		return (1);
	}
	else if (line[i] == '>')
	{
		tokenized->token = REDIR_OUTPUT;
		tokenized->element = null_exit(ft_strdup(">"));
		return (1);
	}
	else if (line[i] == '|')
	{
		tokenized->token = PIPE;
		tokenized->element = null_exit(ft_strdup("|"));
		return (1);
	}
	return (0);
}

static int	get_quoted(char *line, int i, t_tokenized *tokenized)
{
	char	token;
	int		current_pos;
	ssize_t	quote_length;

	token = line[i];
	quote_length = get_index(&line[i + 1], token);
	if (quote_length < 0 || !line[i + 1])
	{
		tokenized->token = UNCLOSED;
		if (!line[i + 1])
		{
			tokenized->element = NULL;
			return (1);
		}
		current_pos = i;
		while (line[i])
			i++;
		tokenized->element = null_exit(ft_substr(line, current_pos + 1, i));
		return (i - current_pos);
	}
	if (token == '\'')
		tokenized->token = SINGLE_QUOTED;
	if (token == '\"')
		tokenized->token = DOUBLE_QUOTED;
	tokenized->element = null_exit(ft_substr(line, i + 1, quote_length));
	return (quote_length + 2);
}

static int	get_word(char *line, int i, t_tokenized *tokenized)
{
	int	start;

	start = i;
	tokenized->token = WORD;
	while (line[i] && !ft_strchr("<>|\'\"", line[i]) \
			&& !ft_strchr(WHITESPACE, line[i]))
		i++;
	tokenized->element = null_exit(ft_substr(&line[start], 0, i - start));
	return (i);
}

t_tokenized	create_token(char *line)
{
	t_tokenized	tokenized;
	static int	i = 0;

	while (line[i] == ' ')
		i++;
	if (line[i] == '\'' || line[i] == '\"')
		i += get_quoted(line, i, &tokenized);
	else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		i += get_sym(line, i, &tokenized);
	else if (line[i])
		i += get_word(line, i, &tokenized);
	else
	{
		tokenized.token = END;
		tokenized.element = NULL;
		i = 0;
	}
	return (tokenized);
}
