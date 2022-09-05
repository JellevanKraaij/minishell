#include "minishell.h"
#include "environment.h"
#include <libft.h>

/**
 * @brief lookup the value of variable \p name in environment
 * 
 * @param name variable name
 * @return char* non modifieable reference to value
 */
char	*ft_getenv(const char *name)
{
	size_t	len;
	char	**ep;

	len = ft_strlen(name);
	ep = ft_getenviron();
	while (*ep)
	{
		if (ft_strncmp(*ep, name, len) == 0)
			return (&(*ep)[len + 1]);
		ep++;
	}
	return (NULL);
}
