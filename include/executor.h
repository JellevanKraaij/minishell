#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include <libft.h>

# define WHITESPACE " "

# define PIPE_OUT_WRITE 1
# define PIPE_IN_READ 0

# define FILE_OUT 1
# define FILE_IN 0

typedef struct s_childs
{
	int		child_count;
	pid_t	child;
	int		pipe_fd[2][2];
}	t_childs;

int		builtin_exit(const char **argv, const char **envp);
int		builtin_pwd(const char **argv, const char **envp);
int		builtin_echo(const char **argv, const char **envp);
int		builtin_cd(const char **argv, const char **envp);
int		builtin_env(const char **argv, const char **envp);
int		builtin_export(const char **argv, const char **envp);
int		builtin_unset(const char **argv, const char **envp);
void	ft_setenv(const char *name, const char *value, int overwrite);
void	ft_unsetenv(const char *name);
int		single_command(t_command *cmd);
void	open_dup_file(void *file_pointer);
int		multiple_commands(t_command *cmd, t_childs *childs, int last_cmd);
int		builtin_process(char **argv_array);
char	*find_path(char *cmd);

#endif