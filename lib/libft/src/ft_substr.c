/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 15:45:07 by jvan-kra      #+#    #+#                 */
/*   Updated: 2021/10/22 14:41:24 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	if (start > ft_strnlen(s, start + len))
		return (ft_strdup(""));
	return (ft_strndup(s + start, len));
}
