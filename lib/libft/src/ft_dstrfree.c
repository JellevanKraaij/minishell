/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dstrfree.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvna-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 11:30:08 by jvna-kra      #+#    #+#                 */
/*   Updated: 2022/08/11 11:30:08 by jvna-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dstrfree(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
