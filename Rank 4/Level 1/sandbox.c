#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
		return (-1);

	if (pid == 0)
	{
		alarm(timeout);
		f();
		exit(0);
	}

	if (waitpid(pid, &status, 0) == -1)
		return (-1);

	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
		{
			if (verbose) printf("Nice function!\n");
			return (1);
		}
		if (verbose) printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
		return (0);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGALRM)
		{
			if (verbose) printf("Bad function: timed out after %u seconds\n", timeout);
		}
		else
		{
			if (verbose) printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
		}
		return (0);
	}
	return (0);
}