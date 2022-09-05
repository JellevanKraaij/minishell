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
	size_t	ep_len;

	if (!overwrite && ft_getenv(name) != NULL)
		return ;
	ft_unsetenv(name);
	ep = ft_getenviron();
	ep_len = ft_dstrlen(ep);
	ep = null_exit(ft_realloc((void *)ep, sizeof(char **) * (ep_len + 1), \
	sizeof(char **) * (ep_len + 2)));
	if (value != NULL)
		ep[ep_len] = null_exit(ft_strjoin3(name, ENV_SEP, value));
	else
		ep[ep_len] = null_exit(ft_strdup(name));
	ep[ep_len + 1] = NULL;
	ft_setenviron(ep);
}
