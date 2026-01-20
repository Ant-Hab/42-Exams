#include <stdio.h>

void solve(char *s, int i, int bal, int l, int r)
{
    if (!s[i])
    {
        if (!bal && !l && !r)
            puts(s);
        return;
    }

    char c = s[i];

    if ((c == '(' && l) || (c == ')' && r))
    {
        s[i] = ' ';
        solve(s, i + 1, bal, l - (c == '('), r - (c == ')'));
        s[i] = c;
    }

    if (c != ')' || bal)
        solve(s, i + 1, bal + (c == '(') - (c == ')'), l, r);
}

int main(int ac, char **av)
{
    int l = 0, r = 0;

    if (ac != 2)
        return (0);

    for (int i = 0; av[1][i]; i++)
    {
        if (av[1][i] == '(')
            l++;
        else if (av[1][i] == ')')
            l ? l-- : r++;
    }

    solve(av[1], 0, 0, l, r);
    return (0);
}