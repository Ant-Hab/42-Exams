#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    int n = 0;
    while (av[1][n])
        n++;
    char *s = malloc(n + 1);
    if (!s)
        return 1;
    for (int i = 0; i <= n; i++)
        s[i] = av[1][i];
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (s[i] > s[j])
            {
                char t = s[i]; s[i] = s[j]; s[j] = t;
            }
    while (1)
    {
        puts(s);
        int i = n - 2;
        while (i >= 0 && s[i] >= s[i + 1])
            i--;
        if (i < 0)
            break;
        int j = n - 1;
        while (s[j] <= s[i])
            j--;
        char t = s[i]; s[i] = s[j]; s[j] = t;
        int l = i + 1, r = n - 1;
        while (l < r)
        {
            t = s[l]; s[l] = s[r]; s[r] = t;
            l++; r--;
        }
    }
    free(s);
    return 0;
}
