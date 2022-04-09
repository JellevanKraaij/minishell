#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

void	*null_exit(void	*ptr)
{
	if (ptr != NULL)
		return (ptr);
	perror_exit("minishell:", 1);
}

void	perror_exit(const char *s, int error_code)
{
	perror(s);
	exit(error_code);
}
