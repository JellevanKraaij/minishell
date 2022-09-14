#include "minishell.h"
#include "environment.h"
#include <libft.h>

/**
 * @brief remove variable \p from process environment
 * 
 * @param name variable to remove
 */

void	ft_unsetenv(const char *name)
{
	char	**ep;
	char	**sp;
	char	*tmp;

	tmp = null_exit(ft_strjoin(name, "="));
	ep = ft_getenviron();
	while (*ep)
	{
		if (ft_strcmp(*ep, tmp) == 0)
		{
			free(*ep);
			sp = ep;
			while (*sp)
			{
				*sp = *(sp + 1);
				sp++;
			}
		}
		ep++;
	}
	free(tmp);
	ft_setenviron(ft_getenviron());
}
