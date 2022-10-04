/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:43:49 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:43:49 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "libft.h"
#include "environment.h"

static const t_builtin	g_builtins[] = {
{.name = "exit", .function = builtin_exit},
{.name = "echo", .function = builtin_echo},
{.name = "cd", .function = builtin_cd},
{.name = "env", .function = builtin_env},
{.name = "pwd", .function = builtin_pwd},
{.name = "export", .function = builtin_export},
{.name = "unset", .function = builtin_unset}
};

t_builtin_f	lookup_builtin(char *cmd)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_builtins) / sizeof(t_builtin))
	{
		if (ft_strcmp(cmd, g_builtins[i].name) == 0)
			return (g_builtins[i].function);
		i++;
	}
	return (NULL);
}

int	execute_builtin(t_command *cmd, t_builtin_f builtin_function)
{
	char	**env;
	int		ret;

	env = ft_getenviron_value();
	ret = builtin_function((const char **)cmd->argv, \
		(const char **)env);
	ft_dstrfree(env);
	return (ret);
}

int	isvalid_key(char *name)
{
	int	i;

	i = 1;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (1);
	while (name[i])
	{
		if (!ft_isalpha(name[i]) && name[i] != '_' && !ft_isalnum(name[i]))
			return (1);
		i++;
	}
	return (0);
}
