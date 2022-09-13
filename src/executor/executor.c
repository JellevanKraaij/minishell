#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"

int	execute_cmd(t_list *commands)
{
	size_t		cmd_count;
	int			ret_value;
	t_list		*created_files;

	created_files = NULL;
	if (heredoc_exec(commands, &created_files) == 1)
	{
		delete_files(&created_files);
		return (1);
	}
	cmd_count = ft_lstsize(commands);
	if (cmd_count == 1)
		ret_value = single_command(commands->content);
	else
		ret_value = multiple_commands(commands);
	delete_files(&created_files);
	return (ret_value);
}
