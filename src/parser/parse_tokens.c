#include "minishell.h"
#include "parser.h"
#include "libft.h"

enum states{
	COMMAND,
	ARGUMENT,
};

t_list *parse_tokens(t_list *tokens)
{
	t_list		*ret;
	enum states	state;
	t_token		token;
	t_command	*cmd;

	state = COMMAND;
	ret = NULL;
	while(tokens != NULL)
	{
		token = *(t_token *)(tokens->content);
		if (state == COMMAND)
		{
			cmd = init_command();
			if (is_token_type_text(token))
				cmd->cmd = null_exit(ft_strdup(token.str));
			else
			{
				print_error("minishell", "parse error", NULL);
				exit(1);
			}
			state = ARGUMENT;
		}
		else if (state == ARGUMENT)
		{
			if (is_token_type_text(token))
				ft_lstadd_back(&cmd->args, null_exit(ft_lstnew(null_exit(ft_strdup(token.str)))));
			else if (token.type == PIPE)
			{
				ft_lstadd_back(&ret, null_exit(ft_lstnew(cmd)));
				state = COMMAND;
			}
			else
			{
				print_error("minishell", "parse error", NULL);
				exit(1);
			}
		}
		tokens = tokens->next;
	}
	if (state != ARGUMENT)
	{
		print_error("minishell", "parse error", NULL);
		exit(1);
	}
	ft_lstadd_back(&ret, null_exit(ft_lstnew(cmd)));
	return (ret);
}