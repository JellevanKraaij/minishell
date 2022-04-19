#include "minishell.h"
#include <libft.h>
#include <stdio.h>
#include <unistd.h>

void    builtin_exit(int argc, char **argv)
{
    int error_code;

    if (argc > 2)
        print_error(argv[0], "Too many arguments", NULL);
    if (argc == 2)
    {
        error_code = ft_atoi(argv[1]);
        exit(error_code);
    }
    exit(1);
}