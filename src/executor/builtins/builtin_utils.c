#include "minishell.h"
#include "executor.h"
#include "libft.h"

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
