#include "minishell.h"
#include "executor.h"
#include <sys/wait.h>

int	wait_for_childs(int child_count, int last_pid)
{
	int	i;
	int	exit_code;
	int	status;

	i = 0;
	exit_code = 1;
	while (i < child_count)
	{
		if (waitpid(-1, &status, 0) == last_pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = WTERMSIG(status) + 128;
		}
		if (WIFEXITED(status) || WIFSIGNALED(status))
			i++;
	}
	return (exit_code);
}
