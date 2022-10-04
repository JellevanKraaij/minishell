/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga           <jvan-kra/to      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:11 by jvan-kra/     #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:11 by jvan-kra/     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"

/**
 * @brief execute commands presented in the abstract syntact
 * 			list in chronological order
 *
 * @param commands list
 */
void	execute_commands(t_list *commands)
{
	size_t		cmd_count;
	t_list		*created_files;

	if (commands == NULL)
		return ;
	created_files = NULL;
	if (heredoc_exec(commands, &created_files) == 1)
	{
		delete_files(&created_files);
		g_last_exit_code = 1;
		return ;
	}
	cmd_count = ft_lstsize(commands);
	if (cmd_count == 1)
		g_last_exit_code = single_command(commands->content);
	else
		g_last_exit_code = multiple_commands(commands);
	delete_files(&created_files);
}
