/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga           <jvan-kra/to      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:30 by jvan-kra/     #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:30 by jvan-kra/     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <stdio.h>
#include <libft.h>

static void	fprint_token(void *data)
{
	t_token		*token;
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

	token = data;
	printf("type = %-12s | str = '%s'\n", \
	type_str[token->type], token->str);
}

static void	fprint_files(void *data)
{
	t_file		*file;
	const char	*flag_str[] = {
	[INPUT] = "input",
	[INPUT_HEREDOC] = "heredoc",
	[INPUT_HEREDOC_LIT] = "heredoc (do not expand)",
	[OUTPUT] = "output",
	[OUTPUT_APP] = "output app",
	};

	file = data;
	printf(" (name='%s' type='%s')", file->name, flag_str[file->flag]);
}

void	print_commands(t_list *commands)
{
	t_command	*cmd;
	int			i;
	int			j;

	i = 1;
	while (commands != NULL)
	{
		cmd = commands->content;
		printf("COMMAND %d\n{\n    files =", i);
		ft_lstiter(cmd->files, fprint_files);
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

void	print_tokens(t_list *tokens)
{
	ft_lstiter(tokens, fprint_token);
}
