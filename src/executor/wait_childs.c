/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wait_childs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra/tosinga                             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 17:44:26 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/10/04 17:44:26 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <sys/wait.h>

static const char	*g_signal_str[] = {NULL, \
"Hangup: 1\n", \
"\n", \
"Quit: 3\n", \
"Illegal instruction: 4\n", \
"Trace/BPT trap: 5\n", \
"Abort trap: 6\n", \
"EMT trap: 7\n", \
"Floating point exception: 8\n", \
"Killed: 9\n", \
"Bus error: 10\n", \
"Segmentation fault: 11\n", \
"Bad system call: 12\n", \
"", \
"Alarm clock: 14\n", \
"Terminated: 15\n", \
"Urgent I/O condition: 16\n", \
"Suspended (signal): 17\n", \
"Suspended: 18\n", \
"Continued: 19\n", \
"Child exited: 20\n", \
"Stopped (tty input): 21\n", \
"Stopped (tty output): 22\n", \
"I/O possible: 23\n", \
"Cputime limit exceeded: 24\n", \
"Filesize limit exceeded: 25\n", \
"Virtual timer expired: 26\n", \
"Profiling timer expired: 27\n", \
"Window size changes: 28\n", \
"Information request: 29\n", \
"User defined signal 1: 30\n", \
"User defined signal 2: 31\n", \
};

static int	handle_signal(int signal)
{
	if (signal > 0 && signal < 32)
		ft_putstr_fd((char *)g_signal_str[signal], STDOUT_FILENO);
	return (signal + 128);
}

int	wait_for_lastcmd(int child_count, int last_pid)
{
	int	i;
	int	status;
	int	last_status;
	int	waitpid_ret;

	i = 0;
	while (i < child_count)
	{
		waitpid_ret = waitpid(-1, &status, 0);
		if (waitpid_ret < 0)
			perror_exit("minishell", 1);
		if (waitpid_ret == last_pid)
			last_status = status;
		if (WIFEXITED(status) || WIFSIGNALED(status))
			i++;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (handle_signal(WTERMSIG(last_status)));
	return (-1);
}
