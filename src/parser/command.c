#include "minishell.h"
#include "parser.h"
#include "libft.h"

t_command *init_command(void)
{
	t_command *ret;

	ret = null_exit(malloc(sizeof(t_command)));
	ret->args = NULL;
	ret->cmd = NULL;
	return (ret);
}
t_command *destroy_command(t_command *cmd)
{
	free(cmd->cmd);
	ft_lstclear(&cmd->args, free);
	free(cmd);
	return(NULL);
}
