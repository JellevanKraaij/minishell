/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_command.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga           <jvan-kra/to      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:46 by jvan-kra/     #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:46 by jvan-kra/     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"

t_command	*init_command(void)
{
	t_command	*ret;

	ret = null_exit(malloc(sizeof(t_command)));
	ret->argv = NULL;
	ret->files = NULL;
	return (ret);
}

t_command	*destroy_command(t_command *cmd)
{
	ft_lstclear(&cmd->files, ((void (*))(void *)destroy_tfile));
	if (cmd->argv)
		ft_dstrfree(cmd->argv);
	free(cmd);
	return (NULL);
}

void	clear_command(t_command *cmd)
{
	ft_lstclear(&cmd->files, ((void (*))(void *)destroy_tfile));
	if (cmd->argv)
		ft_dstrfree(cmd->argv);
	cmd->argv = NULL;
}
