/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga           <jvan-kra/to      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:18 by jvan-kra/     #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:18 by jvan-kra/     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/**
 * @brief support heredoc input and create list of heredoc files
 *
 * @param commands list
 * @param created_files list
 * @return int succes or failure
 */
int	heredoc_exec(t_list *commands, t_list **created_files)
{
	t_list	*files;
	t_file	*file;

	while (commands)
	{
		files = ((t_command *)commands->content)->files;
		while (files)
		{
			file = files->content;
			if (file->flag == INPUT_HEREDOC || file->flag == INPUT_HEREDOC_LIT)
			{
				if (handle_heredoc(file, created_files) < 0)
					return (1);
			}
			files = files->next;
		}
		commands = commands->next;
	}
	return (0);
}
