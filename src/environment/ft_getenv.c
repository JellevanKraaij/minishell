#include "minishell.h"
#include "environment.h"
#include <libft.h>
#include <stdio.h>

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
	char	*tmp;

	len = ft_strlen(name);
	if (len < 1)
		return (NULL);
	tmp = ft_strjoin(name, "=");
	ep = ft_getenviron();
	while (*ep)
	{
		if (ft_strncmp(*ep, tmp, len + 1) == 0)
		{
			free(tmp);
			return (&(*ep)[len + 1]);
		}
		ep++;
	}
	free(tmp);
	return (NULL);
}
