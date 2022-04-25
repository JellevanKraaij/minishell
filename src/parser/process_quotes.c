#include "minishell.h"
#include "parser.h"
#include "libft.h"

static int	check_unclosed_quotes(t_token status)
{
	if (status != NORMAL)
	{
		print_error("minishell", "unclosed quote", NULL);
		return (1);
	}
	return (0);
}

static int	update_status(t_token *status, char c)
{
	if (c == '\'' || c == '\"')
	{
		if (*status == NORMAL)
		{
			*status = (t_token)c;
			return (1);
		}
		if (*status == (t_token)c)
		{
			*status = NORMAL;
			return (1);
		}
	}
	return (0);
}

t_line_data	*process_quotes(char *line)
{
	size_t			i;
	size_t			j;
	t_token			status;
	t_line_data		*ret;

	i = 0;
	j = 0;
	status = NORMAL;
	ret = init_line_data(ft_strlen(line) + 1);
	while (line[i])
	{
		if (!update_status(&status, line[i]))
		{
			ret->line[j] = line[i];
			ret->token[j] = status;
			j++;
		}
		i++;
	}
	ret->line[j] = '\0';
	ret->token[j] = END;
	if (check_unclosed_quotes(status))
		return (destroy_line_data(ret));
	return (ret);
}
