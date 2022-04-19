#include "minishell.h"
#include <libft.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void    builtin_cd(int argc, char **argv)
{
    if (argc > 2)
        ft_putendl_fd("Too many arguments", STDERR_FILENO);
    if (chdir(argv[1]) < 0)
        print_error(argv[0], strerror(errno), argv[1]);
}