#include "minishell.h"
#include "parser.h"
#include "libft.h"

static int	check_unclosed_quotes(t_quote_stat status)
{
	if (status != NORMAL)
	{
		print_error("minishell", "unclosed quote", NULL);
		return (1);
	}
	return (0);
}

static int	update_status(t_quote_stat *status, char c)
{
	if (c == '\'' || c == '\"')
	{
		if (*status == NORMAL)
		{
			*status = (t_quote_stat)c;
			return (1);
		}
		if (*status == (t_quote_stat)c)
		{
			*status = NORMAL;
			return (1);
		}
	}
	return (0);
}

t_line_meta	*process_quotes(char *line)
{
	size_t			i;
	size_t			j;
	t_quote_stat	status;
	t_line_meta		*ret;

	i = 0;
	j = 0;
	status = NORMAL;
	ret = init_meta_char(ft_strlen(line) + 1);
	while (line[i])
	{
		if (!update_status(&status, line[i]))
		{
			ret->line[j] = line[i];
			ret->status[j] = status;
			j++;
		}
		i++;
	}
	ret->line[j] = '\0';
	ret->status[j] = END;
	if (check_unclosed_quotes(status))
		return (destroy_meta_char(ret));
	return (ret);
}
