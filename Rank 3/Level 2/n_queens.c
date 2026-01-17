#include <stdio.h>
#include <stdlib.h>

void solve(int *q, int n, int c)
{
    if (c == n)
    {
        for (int i = 0; i < n; i++)
            fprintf(stdout, "%d%c", q[i], i == n - 1 ? '\n' : ' ');
        return;
    }
    for (int r = 0; r < n; r++)
    {
        int ok = 1;
        for (int i = 0; i < c; i++)
        {
            int d = q[i] - r;
            if (d == 0 || d == c - i || d == i - c)
                ok = 0;
        }
        if (ok)
        {
            q[c] = r;
            solve(q, n, c + 1);
        }
    }
}

int main(int ac, char **av)
{
    if (ac == 2)
    {
        int n = atoi(av[1]);
        int *q = malloc(sizeof(int) * n);
        if (q)
        {
            solve(q, n, 0);
            free(q);
        }
    }
    return 0;
}