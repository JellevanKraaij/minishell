/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lsttoarray.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvna-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 16:19:29 by jvna-kra      #+#    #+#                 */
/*   Updated: 2022/06/28 16:19:29 by jvna-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	**ft_lsttoarray(t_list *lst, void *(*dup)(void *))
{
	void	**ret;
	int		idx;

	if (lst == NULL)
		return (NULL);
	ret = malloc((ft_lstsize(lst) + 1) * sizeof(void *));
	if (ret == NULL)
		return (NULL);
	idx = 0;
	while (lst)
	{
		ret[idx] = (*dup)(lst->content);
		idx++;
		lst = lst->next;
	}
	ret[idx] = NULL;
	return (ret);
}
