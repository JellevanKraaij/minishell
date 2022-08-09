/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dstrlen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvna-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 15:55:21 by jvna-kra      #+#    #+#                 */
/*   Updated: 2022/08/09 15:55:21 by jvna-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_dstrlen(const char **str)
{
	size_t	len;

	len = 0;
	while (str[len] != NULL)
		len++;
	return (len);
}
