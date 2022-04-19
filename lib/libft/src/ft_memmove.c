/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:44:10 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/10/20 14:20:00 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memcpy_rev(void *dst, const void *src, size_t n)
{
	void	*_dst;

	if (src == dst)
		return (dst);
	_dst = dst;
	while (n > 0)
	{
		n--;
		((char *)dst)[n] = ((char *)src)[n];
	}
	return (_dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
		ft_memcpy_rev(dst, src, len);
	return (dst);
}
