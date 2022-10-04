/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:02 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:02 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "environment.h"
#include "libft.h"

int	print_exp(char **envp);

static int	export_only_name(const char *param)
{
	if (isvalid_key((char *)param))
	{
		print_error("minishell: export", (char *)param, \
			"not a valid identifier");
		return (1);
	}
	ft_setenv(param, NULL, 0);
	return (0);
}

static int	export_arg(const char *param)
{
	char	*name;
	char	*value;
	char	*index_p;
	size_t	index;

	index_p = ft_strchr(param, '=');
	if (index_p == NULL)
		return (export_only_name(param));
	index = index_p - param;
	name = null_exit(ft_strndup(param, index));
	if (isvalid_key(name))
	{
		print_error("minishell: export", (char *)param, \
					"not a valid identifier");
		free(name);
		return (1);
	}
	value = null_exit(ft_strdup(&param[index + 1]));
	ft_setenv(name, value, 1);
	free(name);
	free(value);
	return (0);
}

int	builtin_export(const char **argv, const char **envp)
{
	size_t	i;
	size_t	ret;

	(void)envp;
	if (argv[1] == NULL)
		return (print_exp((char **)ft_getenviron()));
	i = 1;
	ret = 0;
	while (argv[i] != NULL)
	{
		if (export_arg(argv[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
