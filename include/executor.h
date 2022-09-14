#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"

# define WHITESPACE " "

# define PIPE_OUT_WRITE 1
# define PIPE_IN_READ 0

# define FILE_OUT 1
# define FILE_IN 0

# define HEREDOC_FILENAME "/tmp/minishell"

# define HEREDOC_CREATE 0
# define HEREDOC_DELETE 1

typedef struct s_childs
{
	int		child_count;
	pid_t	child;
	int		pipe_fd[2][2];
}	t_childs;

typedef int	(*t_builtin_f)(const char **argv, const char **envp);

typedef struct s_builtin
{
	char		*name;
	t_builtin_f	function;
}	t_builtin;

int			single_command(t_command *cmd);
int			multiple_commands(t_list *commands);
void		first_cmd(t_command *cmd, int pipe_out[2]);
void		mid_cmd(t_command *cmd, int pipe_in, int pipe_out[2]);
int			final_cmd(t_command *cmd, int pipe_in);

int			heredoc_exec(t_list *commands, t_list **created_files);
int			handle_heredoc(t_file *file, t_list **created_files);
void		delete_files(t_list **created_files);

int			wait_for_childs(int child_count, int last_pid);
void		check_executable(char *path);
char		*lookup_executable(char *cmd);
char		*find_path(char *cmd);
void		open_dup_file(void *file_pointer);
int			isvalid_key(char *name);

t_builtin_f	lookup_builtin(char *cmd);
int			execute_builtin(t_command *cmd, t_builtin_f builtin_function);

int			builtin_exit(const char **argv, const char **envp);
int			builtin_pwd(const char **argv, const char **envp);
int			builtin_echo(const char **argv, const char **envp);
int			builtin_cd(const char **argv, const char **envp);
int			builtin_env(const char **argv, const char **envp);
int			builtin_export(const char **argv, const char **envp);
int			builtin_unset(const char **argv, const char **envp);

#endif