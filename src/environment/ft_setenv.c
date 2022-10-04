/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_setenv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:43:45 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:43:45 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include <libft.h>
/**
 * @brief add or modify variable \p name in environment
 *
 * @param name variable name
 * @param value variable value
 * @param overwrite overwrite existing value
 */
void	ft_setenv(const char *name, const char *value, int overwrite)
{
	char	**ep;
	char	*tmp;
	size_t	ep_len;

	if (!overwrite && ft_getenv(name) != NULL)
		return ;
	if (value != NULL)
		tmp = null_exit(ft_strjoin3(name, ENV_SEP, value));
	else
		tmp = null_exit(ft_strdup(name));
	ft_unsetenv(name);
	ep = null_exit(ft_dstrdup(ft_getenviron()));
	ep_len = ft_dstrlen(ep);
	ep = null_exit(ft_reallocf((void *)ep, sizeof(char **) * (ep_len + 1), \
	sizeof(char **) * (ep_len + 2)));
	ep[ep_len] = tmp;
	ep[ep_len + 1] = NULL;
	ft_setenviron(ep);
}
