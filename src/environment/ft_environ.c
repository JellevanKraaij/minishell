#include "minishell.h"
#include "environment.h"
#include <libft.h>

extern char	**environ;

static char	**_environ(char **new_env)
{
	static char	**env = NULL;

	if (new_env != NULL)
	{
		if (env != NULL)
			ft_dstrfree(env);
		env = new_env;
	}
	if (env == NULL)
		env = null_exit(ft_dstrdup(environ));
	return (env);
}

/**
 * @brief get pointer to process environment
 * 
 * @return char** pointer to environment
 */

char	**ft_getenviron(void)
{
	return (_environ(NULL));
}

/**
 * @brief get copy of process environment only with VALUE
 * 
 * @return char** 
 */

char	**ft_getenviron_value(void)
{
	char	**env;
	char	**ep;
	char	**sp;

	env = null_exit(ft_dstrdup(ft_getenviron()));
	ep = env;
	while (*ep)
	{
		if (ft_strchrset(*ep, ENV_SEP) == NULL)
		{
			free(*ep);
			sp = ep;
			while (*sp)
			{
				*sp = *(sp + 1);
				sp++;
			}
		}
		else
			ep++;
	}
	return (env);
}

/**
 * @brief copy given enviroment to process environment
 * 
 * @param env environment to copy
 */

void	ft_setenviron(char **env)
{
	_environ(env);
}
