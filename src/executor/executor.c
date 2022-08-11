#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>

void	fork_error(pid_t pid)
{
	if (pid < 0)
		perror("Fork did not succeed\n");
}

extern char	**environ;

char	*exec_cmd(char *cmd)
{
	int		i;
	char	*cmd_path;
	char	**paths;

	paths = env_paths(); //add jelle function
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, 0) == 0)
			if(execve(cmd_path, ) - 1) //add correct input
				//execve error
		i++;
	}
	print_error("minishell", cmd, "command not found");
}

int	single_command(t_command *cmd)
{
	pid_t	child_id;

	builtin_process(cmd->argv);
	child_id = fork_check(fork());	//what type of error forking?
	if (child_id == 0)
		exec_cmd(cmd->argv[0]);

}

int	multiple_commands(t_list *commands, int cmd_count, t_childs *childs)
{
	char	*path;
	int		pipe_tot;
	int		i;

	i = 0;
	pipe_tot = ft_lstsize(commands);
	if (cmd_count < pipe_tot)
	{
		pipe(childs->pipe_fd[i]);
		cmd_count++;
	}
	fork();


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

// geen pipe bij 1 command, wel fork. als pipe dan eerst fork. 

void	execute_cmd(t_list *commands)
{
	t_command	*cmd;
	t_childs	*childs; // make sure that every child can get to all info.
	int			cmd_count;

	cmd_count = 0;
	cmd = ((t_command *)commands->content);
	if (!commands->next)
		single_command(cmd);
	else
	{
		while (commands)
		{
			multiple_commands(commands, cmd_count, &childs);
			commands = commands->next;
			cmd_count++;
		}
	}
}

