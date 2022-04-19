/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:45:00 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/10/19 15:45:00 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strnmatch(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (*haystack && len)
	{
		if (ft_strnmatch(haystack, needle, len))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}

static int	ft_strnmatch(const char *s1, const char *s2, size_t n)
{
	while (*s2)
	{
		if (*s1 != *s2 || !n)
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (1);
}
