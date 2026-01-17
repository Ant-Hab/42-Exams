#include <stdio.h>
#include <stdlib.h>

void solve(int *set, int n, int *sub, int len, int idx, int sum, int target)
{
    if (sum == target)
    {
        for (int i = 0; i < len; i++)
            printf("%d%c", sub[i], (i == len - 1) ? '\n' : ' ');
        if (len == 0)
            printf("\n");
    }
    for (int i = idx; i < n; i++)
    {
        sub[len] = set[i];
        solve(set, n, sub, len + 1, i + 1, sum + set[i], target);
    }
}

int main(int ac, char **av)
{
    if (ac >= 2)
    {
        int n = ac - 2;
        int *arr = malloc(sizeof(int) * ((n * 2) + 1));
        if (!arr)
            return 1;
        for (int i = 0; i < n; i++)
            arr[i] = atoi(av[i + 2]);
        solve(arr, n, arr + n, 0, 0, 0, atoi(av[1]));
        free(arr);
    }
    return 0;
}