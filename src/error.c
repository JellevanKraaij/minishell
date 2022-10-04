/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:56 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:56 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

void	*null_exit(void	*ptr)
{
	if (ptr != NULL)
		return (ptr);
	perror_exit("minishell", 1);
}

void	perror_exit(const char *s, int error_code)
{
	perror(s);
	exit(error_code);
}

void	print_error(char *name, char *error_desc, char *error)
{
	if (name == NULL || error_desc == NULL)
		return ;
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_desc, STDERR_FILENO);
	if (error == NULL)
	{
		ft_putendl_fd("", STDERR_FILENO);
		return ;
	}
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
}
