#include "minishell.h"
#include "parser.h"
#include <libft.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static const char	*type_to_string(t_type type)
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
	[SEPERATOR] = "SEPERATOR",
	[UNCLOSED] = "UNCLOSED QUOTE",
	};

	return (type_str[type]);
}

static const char	*flag_to_string(t_fileflags flag)
{
	const char	*flag_str[] = {
	[INPUT] = "input",
	[INPUT_HEREDOC] = "heredoc",
	[INPUT_HEREDOC_LIT] = "heredoc (do not expand)",
	[OUTPUT] = "output",
	[OUTPUT_APP] = "output app",
	};

	return (flag_str[flag]);
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
	t_file	*file;
	t_command *cmd;
	int	i, j;

	i = 1;
	while(commands != NULL)
	{
		cmd = commands->content;
		printf("COMMAND %d\n{\n    files =", i);
		tmp = cmd->files;
		while(tmp != NULL)
		{
			file = tmp->content;
			printf(" (name='%s' type='%s')", file->name, flag_to_string(file->flag));
			tmp = tmp->next;
		}
		printf("\n    argv =");
		j = 0;
		while (cmd->argv && cmd->argv[j])
		{
			printf(" '%s'", cmd->argv[j]);
			j++;
		}
		printf("\n}\n");
		i++;
		commands = commands->next;
	}
}

void	parse_exec(char *line)
{
	t_list	*tokens;
	t_list	*combined_tokens;
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
	combined_tokens = combine_tokens(tokens);
	ft_lstclear(&tokens, ((void (*))(void *)destroy_token));
	commands = parse_tokens(combined_tokens);
	ft_lstclear(&combined_tokens, ((void (*))(void *)destroy_token));
	print_commands(commands);
}
