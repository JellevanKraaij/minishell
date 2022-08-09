#include "minishell.h"
#include <stdio.h>
#include "parser.h"
#include "libft.h"

// void	fork_error(void)
// {
// 	perror("Fork did not succeed\n");
// }

char **argv_array(t_list *lst)
{
    int     length;
    char    **commands;
    int     counter;

    length  = ft_lstsize(lst);
    counter = 0;
    commands = null_exit((char**)malloc(sizeof(char*) * (length + 1)));
    while (lst)
    {
        commands[counter] = null_exit(ft_strdup(lst->content));
        lst = lst->next;
        counter++;
    }
    commands[counter] = NULL;
    return(commands);
}

// int    builtin_process(char *str[], int pipe_flag)
// {
//     if (!ft_strncmp(str[0], "exit", 5) && !pipe_flag)
//     {
//         exit (0); //whaa
//     }
//     if (!ft_strncmp(str[0], "echo", 5) && !ft_strncmp(str[1], "-n", 3) && !pipe_flag)
//     {
//         exit (0);
//     }
//     return (1);
// }

// void    fork_process(t_list *commands, int pipe_flag)
// {
//     t_command   *current_cmd;
//     char        *path;
//     t_childs    childs;
//     //forking

//     while(commands->next)
//     {
//         current_cmd = commands->content;
//         child_process();
//         // open_files(current_cmd->files);
//         if(!builtin_process(current_cmd->argv_array, pipe_flag))
//             path = get_cmd_path(current_cmd->argv_array[0]);
//     }

// }

void    execute_cmd(t_list *commands)
{
    while(commands)
    {
        commands->argv_array = argv_array(commands->argv_list);
        
    }
    // t_command   *current_cmd;
    // int         pipe_flag;

    // pipe_flag = 0;
    // while(commands)
    // {
    //     if (commands->next)
    //         pipe_flag = 1;
    //     current_cmd = commands->content;
    //     current_cmd->argv_array = argv_array(current_cmd->argv_list);
    //     commands = commands->next;
    // }
    // fork_process(commands, pipe_flag);
        // exec_process();
}

