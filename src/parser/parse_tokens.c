#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>

static int	handle_file(t_command *cmd, t_token token, t_fileflags fileflags)
{
	if (!is_token_type_text(token))
	{
		clear_command(cmd);
		return (-1);
	}
	ft_lstadd_back(&cmd->files, \
		null_exit(ft_lstnew(null_exit(create_tfile(token.str, fileflags)))));
	return (0);
}

t_list	*parse_command(t_command *cmd, t_list *tokens)
{
	t_token			token;
	t_fileflags		fileflags;

	fileflags = INVALID;
	while (tokens != NULL)
	{
		token = *(t_token *)(tokens->content);
		if (fileflags != INVALID)
		{
			if (handle_file(cmd, token, fileflags) < 0)
				break ;
			fileflags = INVALID;
		}
		else if (is_token_type_redir(token))
			fileflags = token_to_fileflag(token);
		else if (token.type == PIPE)
			break ;
		else
			ft_lstadd_back(&cmd->argv_list, \
				null_exit(ft_lstnew(null_exit(ft_strdup(token.str)))));
		tokens = tokens->next;
	}
	if (fileflags != INVALID)
		clear_command(cmd);
	return (tokens);
}

static void	*parser_error(t_list *tokens)
{
	char	*error_text;

	if (tokens == NULL)
		error_text = "newline";
	else
		error_text = ((t_token *)(tokens->content))->str;
	print_error("minishell", "syntax error near unexpected token", error_text);
	return (NULL);
}

t_list	*parse_tokens(t_list *tokens)
{
	t_list		*ret;
	t_command	*cmd;

	ret = NULL;
	while (tokens != NULL)
	{
		cmd = init_command();
		tokens = parse_command(cmd, tokens);
		ft_lstadd_back(&ret, null_exit(ft_lstnew(cmd)));
		if (cmd->argv_list == NULL && cmd->files == NULL)
		{
			ft_lstclear(&ret, ((void (*))(void *)destroy_command));
			return (parser_error(tokens));
		}
		if (tokens == NULL)
			break ;
		tokens = tokens->next;
		if (tokens == NULL)
		{
			ft_lstclear(&ret, ((void (*))(void *)destroy_command));
			return (parser_error(tokens));
		}
	}
	return (ret);
}
