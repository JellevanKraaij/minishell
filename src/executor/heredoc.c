#include "minishell.h"
#include "executor.h"

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
