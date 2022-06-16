#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>

const char	*type_to_string(t_type type)
{
	const char	*type_str[] = {
	[DEFAULT] = "DEFAULT",
	[SINGLE_QUOTED] = "SINGLE_QUOTED",
	[DOUBLE_QUOTED] = "DOUBLE_QUOTED",
	[REDIR_INPUT] = "REDIR_INPUT",
	[HEREDOC] = "HEREDOC",
	[REDIR_OUTPUT] = "REDIR_OUTPUT",
	[REDIR_OUTPUT_APPEND] = "REDIR_OUTPUT_APPEND",
	[PIPE] = "PIPE",
	[UNCLOSED] = "UNCLOSED QUOTE",
	};

	return (type_str[type]);
}

void	fprint_token(void *data)
{
	t_token	*token;

	token = data;
	printf("type = %-12s | str = '%s'\n", \
	type_to_string(token->type), token->str);
}

void	print_commands(t_list *commands)
{
	t_list *tmp;
	t_command *cmd;
	int	i;

	while(commands != NULL)
	{
		cmd = commands->content;
		printf("cmd='%s'", cmd->cmd);
		i = 0;
		tmp = cmd->args;
		while (tmp != NULL)
		{
			printf(" arg[%d]='%s'",i, (char *)tmp->content);
			i++;
			tmp = tmp->next;
		}
		if (commands->next != NULL)
			printf(" | ");
		else
			printf("\n");
		commands = commands->next;
	}
}

void	parse_exec(char *line)
{
	t_list	*tokens;
	t_list	*commands;

	if (line == NULL)
	{
		rl_clear_history();
		exit(0);
	}
	if (*line == '\0')
		return ;
	tokens = null_exit(ft_lstnew(create_token(line, ft_strlen(line), DEFAULT)));
	update_token_list(&tokens, lexer_process);
	update_token_list(&tokens, expand_vars);
	update_token_list(&tokens, split_tokens);
	ft_lstiter(tokens, fprint_token);
	commands = parse_tokens(tokens);
	print_commands(commands);
}
