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
	size_t	len;
	char	**ep;
	char	**sp;

	len = ft_strlen(name);
	ep = ft_getenviron();
	while (*ep)
	{
		if (ft_strncmp(*ep, name, len) == 0)
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
	ft_setenviron(ft_getenviron());
}
