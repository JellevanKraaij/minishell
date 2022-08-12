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
		env = null_exit(ft_dstrdup(new_env));
	}
	if (env == NULL)
		env = null_exit(ft_dstrdup(environ));
	return (env);
}

/**
 * @brief get copy of process environment
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
