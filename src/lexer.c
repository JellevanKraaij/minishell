#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	get_sym(char *line, int i, t_tokenized *tokenized)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		tokenized->token = RED_OUT_APPEND;
		tokenized->element = ">>";
		return (2);
	}
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		tokenized->token = RED_IN;
		tokenized->element = ">>";
		return (2);
	}
	else if (line[i] == '<')
	{
		tokenized->token = RED_INPUT;
		tokenized->element = "<";
		return (1);
	}
	else if (line[i] == '>')
	{
		tokenized->token = RED_OUTPUT;
		tokenized->element = ">";
		return (1);
	}
	else if (line[i] == '|')
	{
		tokenized->token = PIPE;
		tokenized->element = "|";
		return (1);
	}
	return (0);
}

static int	get_quoted(char *line, int i, t_tokenized *tokenized)
{
	int	token;

	token = line[i];
	if (!ft_strchr(&line[i + 1], token) || !line[i + 1])
	{
		printf("ERROR: No closing quote\n");
		tokenized->token = UNCLOSED;
		tokenized->element = NULL;
		return (0);
	}
	if (token == '\'')
		tokenized->token = SQUOTED;
	if (token == '\"')
		tokenized->token = DQUOTED;
	tokenized->element = ft_substr(&line[i + 1], 0, ft_strchr(&line[i + 1], token) - ft_strchr(&line[i], token) - 1);
	return (ft_strchr(&line[i + 1], token) - ft_strchr(&line[i], token) + 1);
}

static int	get_word(char *line, int i, t_tokenized *tokenized)
{
	int	start;

	start = i;
	tokenized->token = WORD;
	while(line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>' && line[i] != '|' && line[i] != '\''  && line[i] != '\"')
		i++;
	tokenized->element = ft_substr(&line[start], 0, i - start);
	return (i);
}

t_tokenized	create_token(char *line)
{
	t_tokenized	tokenized;
	static int	i = 0;

	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\'' || line[i] == '\"')
		{
			i += get_quoted(line, i, &tokenized); //-1 if no quote end
			return (tokenized);
		}
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			i += get_sym(line, i, &tokenized);
			return (tokenized);
		}
		else
			i += get_word(line, i, &tokenized);
		return (tokenized);
	i++;
	}
	tokenized.token = END;
	tokenized.element = NULL;
	return (tokenized);
}
