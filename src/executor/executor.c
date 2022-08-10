#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>

// void	fork_error(void)
// {
// 	perror("Fork did not succeed\n");
// }



char	**argv_array(t_list *lst)
{
	int		length;
	char	**commands;
	int		counter;

	length	= ft_lstsize(lst);
	counter = 0;
	commands = null_exit((char**)malloc(sizeof(char*) * (length + 1)));
	while (lst)
	{
		commands[counter] = null_exit(ft_strdup(lst->content));
		lst = lst->next;
		counter++;
	}
	commands[counter] = NULL;
	return (commands);
}

int	builtin_process(char **argv_array)
{
	if (!ft_strncmp(argv_array[0], "exit", 5))
		builtin_exit((const char **)argv_array, NULL);
	else if (!ft_strncmp(argv_array[0], "echo", 5))
		builtin_echo((const char **)argv_array, NULL);
	else if (!ft_strncmp(argv_array[0], "cd", 3))
		builtin_cd((const char **)argv_array, NULL);
	else if (!ft_strncmp(argv_array[0], "env", 4))
		builtin_env((const char **)argv_array, NULL);
	else if (!ft_strncmp(argv_array[0], "pwd", 3))
		builtin_pwd((const char **)argv_array, NULL);
	// else if (!ft_strncmp(argv_array[0], "export", 7))
		// builtin_export((const char **)argv_array, NULL);
	// else if (!ft_strncmp(argv_array[0], "unset", 6))
	// 	builtin_unset(argv_array);
	return (0);
}

// geen pipe bij 1 command, wel altijd forken

void	fork_process(t_list *commands)
{
	char		*path;
	t_command	*cmd;
	int			pipe_flag;
	// t_childs	childs;
	//forking

	pipe_flag = 0;
	if (commands->next)
		pipe_flag = 1;
	while (commands)
	{
		cmd = ((t_command *)commands->content);
		if (!pipe_flag)
			builtin_process(cmd->argv_array);
		path = get_cmd_path(cmd->argv_array[0]);
		// fork
		// child_process();
		// open_files(cmd->files);
		commands = commands->next;
	}

}

void execute_cmd(t_list	*commands)
{
	t_command	*cmd;
	t_list		*tmp;

	tmp = commands;
    while (tmp)
    {
		cmd = ((t_command *)tmp->content);
        cmd->argv_array = argv_array(cmd->argv_list);
        tmp = tmp->next;
    }
    fork_process(commands);
    // exec_process();
}
