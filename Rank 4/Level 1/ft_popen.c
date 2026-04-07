#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	int		fd[2];
	pid_t	pid;

	if (!file || !argv || (type != 'w' && type != 'r'))
		return (-1);

	if (pipe(fd) == -1)
		return (-1);
	
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}

	if (pid == 0)
	{
		if (type == 'r')
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		else if (type == 'w')
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
		}
		execvp(file, argv);
		exit(1);
	}

	if (type == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}
	else
	{
		close(fd[0]);
		return (fd[1]);
	}
}
