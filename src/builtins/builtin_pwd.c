#include "minishell.h"
#include <libft.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

void    builtin_pwd(int argc, char **argv)
{
    char    wd[PATH_MAX + 1];

    if (argc > 1)
        print_error(argv[0], "Too many arguments", NULL);
    printf("%s\n", getcwd(wd, sizeof(wd)));
}