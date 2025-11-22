#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int ft_atoi(char *s)
{
    int i = 0, sign = 1, n = 0;
    if (!s)
        return 0;
    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
    {
        n = n * 10 + (s[i] - '0');
        i++;
    }
    return n * sign;
}

int is_safe(int *cols, int row, int col)
{
    int i = 0;
    while (i < col)
    {
        if (cols[i] == row || abs(cols[i] - row) == col - i)
            return 0;
        i++;
    }
    return 1;
}

void print_solution(int *cols, int n)
{
    int i = 0;
    while (i < n)
    {
        char buf[12];
        int num = cols[i], j = 11;
        buf[11] = '\0';
        if (num == 0)
            buf[10] = '0';
        else
        {
            while (num > 0)
            {
                buf[--j] = (num % 10) + '0';
                num /= 10;
            }
        }
        write(1, buf + j, 11 - j);
        if (i < n - 1)
            write(1, " ", 1);
        i++;
    }
    write(1, "\n", 1);
}

void solve(int *cols, int n, int col)
{
    if (col == n)
    {
        print_solution(cols, n);
        return;
    }
    int row = 0;
    while (row < n)
    {
        if (is_safe(cols, row, col))
        {
            cols[col] = row;
            solve(cols, n, col + 1);
        }
        row++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int n = ft_atoi(argv[1]);
    if (n <= 0)
        return 0;
    int *cols = (int *)malloc(sizeof(int) * n);
    if (!cols)
        return 1;
    solve(cols, n, 0);
    free(cols);
    return 0;
}
