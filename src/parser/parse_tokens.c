#include "minishell.h"
#include "parser.h"
#include "libft.h"

enum states {ARGV, REDIR};

static t_list	*ft_lstnew_str(char *s)
{
	return (null_exit(ft_lstnew(null_exit(ft_strdup(s)))));
}

static void	*parser_error(char *str, t_command *cmd, t_list *ret)
{
	destroy_command(cmd);
	ft_lstclear(&ret, ((void (*))(void *)destroy_command));
	print_error("minishell", "syntax error near unexpected token", str);
	return (NULL);
}

t_list	*parse_tokens(t_list *tokens)
{
	t_list		*ret;
	enum states	state;
	t_token		token;
	t_command	*cmd;
	t_fileflags	redir_flag;

	state = ARGV;
	ret = NULL;
	cmd = init_command();
	while (tokens != NULL)
	{
		token = *(t_token *)(tokens->content);
		if (state == ARGV)
		{
			if (is_token_type_text(token))
				ft_lstadd_back(&cmd->argv, ft_lstnew_str(token.str));
			else if (is_token_type_redir(token))
			{
				redir_flag = (t_fileflags)token.type;
				state = REDIR;
			}
			else if (token.type == PIPE)
			{
				ft_lstadd_back(&ret, null_exit(ft_lstnew(cmd)));
				cmd = init_command();
			}
			else
				return (parser_error(token.str, cmd, ret));
		}
		else if (state == REDIR)
		{
			if (is_token_type_text(token))
				ft_lstadd_back(&cmd->files, null_exit(ft_lstnew(create_file(token.str, redir_flag))));
			else
				return (parser_error(token.str, cmd, ret));
			state = ARGV;
		}
		tokens = tokens->next;
	}
	if (cmd->argv == NULL)
		return (parser_error("newline", cmd, ret));
	ft_lstadd_back(&ret, null_exit(ft_lstnew(cmd)));
	return (ret);
}