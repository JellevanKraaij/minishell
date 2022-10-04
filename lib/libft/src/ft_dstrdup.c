/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dstrdup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvna-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 14:28:26 by jvna-kra      #+#    #+#                 */
/*   Updated: 2022/08/11 14:28:26 by jvna-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dstrdup(char **str)
{
	size_t	len;
	size_t	i;
	char	**ret;

	len = ft_dstrlen(str);
	ret = malloc((len + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = ft_strdup(str[i]);
		if (ret[i] == NULL)
		{
			ft_dstrfree(ret);
			return (NULL);
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
