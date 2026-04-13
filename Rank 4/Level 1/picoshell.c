#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
    int fd[2];
    int prev = -1;
    int i = 0;
    pid_t pid;

    if (!cmds || !cmds[0])
        return (0);

    while (cmds[i])
    {
        if (cmds[i + 1] && pipe(fd) == -1)
        {
            if (prev != -1)
                close(prev);
            return (1);
        }

        pid = fork();
        if (pid == -1)
        {
            if (cmds[i + 1])
            {
                close(fd[0]);
                close(fd[1]);
            }
            if (prev != -1)
                close(prev);
            return (1);
        }

        if (pid == 0)
        {
            if (prev != -1)
            {
                dup2(prev, 0);
                close(prev);
            }
            if (cmds[i + 1])
            {
                close(fd[0]);
                dup2(fd[1], 1);
                close(fd[1]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }

        if (prev != -1)
            close(prev);

        if (cmds[i + 1])
        {
            close(fd[1]);
            prev = fd[0];
        }
        else
        {
            prev = -1;
        }
        i++;
    }

    if (prev != -1)
        close(prev);

    while (wait(NULL) != -1);
    return (0);
}
