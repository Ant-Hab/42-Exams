#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void h(int s) { (void)s; }

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    pid_t pid;
    int status;
    struct sigaction sa;

    sa.sa_handler = h;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGALRM, &sa, NULL) == -1 || (pid = fork()) == -1)
        return -1;

    if (pid == 0) { f(); exit(0); }

    alarm(timeout);
    if (waitpid(pid, &status, 0) == -1)
    {
        if (errno == EINTR)
        {
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);
            if (verbose) printf("Bad function: timed out after %u seconds\n", timeout);
            return 0;
        }
        return -1;
    }
    alarm(0);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
    {
        if (verbose) printf("Nice function!\n");
        return 1;
    }

    if (verbose && WIFEXITED(status))
        printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
    else if (verbose && WIFSIGNALED(status))
        printf("Bad function: %s\n", strsignal(WTERMSIG(status)));

    return 0;
}
