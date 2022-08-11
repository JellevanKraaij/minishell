/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 15:44:30 by jvan-kra      #+#    #+#                 */
/*   Updated: 2021/10/20 14:28:55 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_free(char **str)
{
	ft_dstrfree(str);
}

static size_t	ft_split_count(char const *s, char c)
{
	size_t	str_cnt;
	size_t	tmp;

	str_cnt = 0;
	while (*s)
	{
		tmp = ft_findchr(s, c);
		s += tmp;
		if (tmp > 0)
			str_cnt++;
		else
			s++;
	}
	return (str_cnt);
}

static char	**ft_split_build(char const *s, char c, char **ret)
{
	size_t	str_cnt;
	size_t	tmp;

	str_cnt = 0;
	while (*s)
	{
		tmp = ft_findchr(s, c);
		if (tmp > 0)
		{
			ret[str_cnt] = ft_substr(s, 0, tmp);
			if (ret[str_cnt] == NULL)
				return (NULL);
			str_cnt++;
			s += tmp;
		}
		else
			s++;
	}
	ret[str_cnt] = NULL;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	ret = (char **)malloc((ft_split_count(s, c) + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	if (ft_split_build(s, c, ret) == NULL)
	{
		ft_split_free(ret);
		return (NULL);
	}
	return (ret);
}
