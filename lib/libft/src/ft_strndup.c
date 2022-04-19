/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:57:28 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/10/20 15:22:51 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;
	size_t	len;

	len = ft_strnlen(src, n);
	dest = malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	dest[len] = '\0';
	return (ft_memcpy(dest, src, len));
}
