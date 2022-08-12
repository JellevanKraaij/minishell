#include "minishell.h"
#include "environment.h"
#include <libft.h>
#include <stdio.h>

/**
 * @brief lookup the value of variable \p name in environment
 * 
 * @param name variable name
 * @return char* freeable copy of the value
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
		{
			printf("return\n");
			return (null_exit(ft_strdup(&(*ep)[len + 1])));
		}
		ep++;
	}
	return (NULL);
}
