/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:44:45 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/10/19 15:44:45 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strnlen(dst, dstsize);
	if (dstlen == dstsize)
		return (srclen + dstlen);
	if (srclen + 1 <= dstsize - dstlen)
		ft_memcpy(dst + dstlen, src, srclen + 1);
	else
	{
		ft_memcpy(dst + dstlen, src, dstsize - dstlen - 1);
		dst[dstsize - 1] = '\0';
	}
	return (srclen + dstlen);
}
