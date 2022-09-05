/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dstrtolst.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvna-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 15:00:42 by jvna-kra      #+#    #+#                 */
/*   Updated: 2022/08/11 15:00:42 by jvna-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_dstrtolst(char **str)
{
	t_list	*ret;
	t_list	*node;
	char	*tmp;

	ret = NULL;
	while (*str)
	{
		tmp = ft_strdup(*str);
		if (tmp == NULL)
		{
			ft_lstclear(&ret, free);
			return (NULL);
		}
		node = ft_lstnew(tmp);
		if (node == NULL)
		{
			free(tmp);
			ft_lstclear(&ret, free);
			return (NULL);
		}
		ft_lstadd_back(&ret, node);
		str++;
	}
	return (ret);
}
