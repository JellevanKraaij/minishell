/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strntrim.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 15:45:05 by jvan-kra      #+#    #+#                 */
/*   Updated: 2021/10/19 15:45:05 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strntrim(char const *s1, char const *set, size_t n)
{
	size_t	start;
	size_t	len;

	start = 0;
	len = ft_strnlen(s1, n - 1);
	while (s1[start] && ft_strchr(set, s1[start]) && start < n)
		start++;
	if (start == n)
		return (ft_strdup(""));
	while (len && ft_strchr(set, s1[len]))
		len--;
	return (ft_substr(s1, start, len - start + 1));
}
