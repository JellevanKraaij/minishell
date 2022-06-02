/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvna-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 19:24:06 by jvna-kra      #+#    #+#                 */
/*   Updated: 2022/05/11 19:24:06 by jvna-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	size_t	s1len;
	size_t	s2len;
	size_t	s3len;
	char	*ret;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s3len = ft_strlen(s3);
	ret = malloc(s1len + s2len + s3len + 1);
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, s1, s1len);
	ft_memcpy(ret + s1len, s2, s2len + 1);
	ft_memcpy(ret + s1len + s2len, s3, s3len + 1);

	return (ret);
}
