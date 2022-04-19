/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:45:02 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/10/20 14:34:36 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ret;

	ret = NULL;
	while (*s)
	{
		if ((unsigned char)(*s) == (unsigned char)c)
			ret = s;
		s++;
	}
	if (c == '\0')
		ret = s;
	return ((char *)ret);
}
