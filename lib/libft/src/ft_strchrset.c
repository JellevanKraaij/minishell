/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchrset.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvna-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 17:32:48 by jvna-kra      #+#    #+#                 */
/*   Updated: 2022/04/26 17:32:48 by jvna-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrset(const char *s, const char *set)
{
	while (*s)
	{
		if (ft_strrchr(set, *s))
			return ((char *)s);
		s++;
	}
	return (NULL);
}
