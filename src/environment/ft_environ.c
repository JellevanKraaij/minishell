#include "minishell.h"
#include "environment.h"
#include <libft.h>

extern char	**environ;

static char	**_environ(char **new_env)
{
	static char	**env = NULL;
	char		**env_old;

	if (new_env != NULL)
	{
		env_old = env;
		env = null_exit(ft_dstrdup(new_env));
		if (env_old != NULL)
			ft_dstrfree(env_old);
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
 * @brief copy given enviroment to process environment
 * 
 * @param env environment to copy
 */

void	ft_setenviron(char **env)
{
	_environ(env);
}
