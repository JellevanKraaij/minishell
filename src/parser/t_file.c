/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_file.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:48 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:48 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"

t_file	*init_tfile(void)
{
	t_file	*ret;

	ret = null_exit(malloc(sizeof(t_file)));
	ret->name = NULL;
	ret->flag = -1;
	return (ret);
}

t_file	*destroy_tfile(t_file *file)
{
	free(file->name);
	free(file);
	return (NULL);
}

t_file	*create_tfile(char *name, t_fileflags flag)
{
	t_file	*ret;

	ret = init_tfile();
	ret->name = null_exit(ft_strdup(name));
	ret->flag = flag;
	return (ret);
}
