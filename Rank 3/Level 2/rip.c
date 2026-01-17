#include <unistd.h>

void solve(char *s, int i, int last, char *p)
{
    int c = 0, k = i;
    while (s[k])
    {
        if (s[k] == *p) c++;
        else if (s[k] == p[1]) c--;
        if (c < 0)
        {
            int j = last;
            while (j <= k)
            {
                if (s[j] == p[1] && (j == last || s[j - 1] != p[1]))
                {
                    s[j] = ' ';
                    solve(s, k + 1, j, p);
                    s[j] = p[1];
                }
                j++;
            }
            return;
        }
        k++;
    }
    char b[4096];
    int l = k, x = 0;
    while (l--) b[x++] = s[l];
    b[x] = 0;
    if (*p == '(')
        solve(b, 0, 0, ")(");
    else
    {
        write(1, b, x);
        write(1, "\n", 1);
    }
}

int main(int ac, char **av)
{
    if (ac == 2)
        solve(av[1], 0, 0, "()");
    return 0;
}
