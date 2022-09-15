#include "minishell.h"
#include "parser.h"
#include "libft.h"

static int	handle_file(t_command *cmd, t_token token, t_fileflags fileflags)
{
	if (!is_token_type_text(token))
	{
		clear_command(cmd);
		return (-1);
	}
	if (fileflags == INPUT_HEREDOC && \
		(token.type == DOUBLE_QUOTED || token.type == SINGLE_QUOTED))
		fileflags = INPUT_HEREDOC_LIT;
	ft_lstadd_back(&cmd->files, \
		null_exit(ft_lstnew(null_exit(create_tfile(token.str, fileflags)))));
	return (0);
}

static void	add_arg_to_cmd(const char *arg, t_command *cmd)
{
	size_t	len;

	if (cmd->argv == NULL)
	{
		len = 0;
		cmd->argv = null_exit(ft_calloc(len + 2, sizeof(char *)));
	}
	else
	{
		len = ft_dstrlen(cmd->argv);
		cmd->argv = null_exit(ft_reallocf(cmd->argv, \
			(len + 1) * sizeof(char *), \
			(len + 2) * sizeof(char *)));
	}
	cmd->argv[len] = null_exit(ft_strdup(arg));
	cmd->argv[len + 1] = NULL;
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
			add_arg_to_cmd(token.str, cmd);
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
	g_last_exit_code = 258;
	return (NULL);
}

t_list	*parse_tokens(t_list *tokens)
{
	t_list		*ret;
	t_command	*cmd;

	ret = NULL;
	if (tokens == NULL)
		return (NULL);
	if (((t_token *)ft_lstlast(tokens)->content)->type == UNCLOSED)
		return (parser_error(NULL));
	while (tokens != NULL)
	{
		cmd = init_command();
		tokens = parse_command(cmd, tokens);
		ft_lstadd_back(&ret, null_exit(ft_lstnew(cmd)));
		if (cmd->argv == NULL && cmd->files == NULL)
		{
			ft_lstclear(&ret, ((void (*))(void *)destroy_command));
			return (parser_error(tokens));
		}
		if (tokens == NULL)
			return (ret);
		tokens = tokens->next;
	}
	ft_lstclear(&ret, ((void (*))(void *)destroy_command));
	return (parser_error(tokens));
}
