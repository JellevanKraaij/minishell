#include "minishell.h"
#include "parser.h"
#include "libft.h"

t_command	*init_command(void)
{
	t_command	*ret;

	ret = null_exit(malloc(sizeof(t_command)));
	ret->argv_list = NULL;
	ret->files = NULL;
	return (ret);
}

t_command	*destroy_command(t_command *cmd)
{
	ft_lstclear(&cmd->files, ((void (*))(void *)destroy_tfile));
	ft_lstclear(&cmd->argv_list, free);
	free(cmd);
	return (NULL);
}

void	clear_command(t_command *cmd)
{
	ft_lstclear(&cmd->files, ((void (*))(void *)destroy_tfile));
	ft_lstclear(&cmd->argv_list, free);
}
