#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

void print_subset(int *subset, int len)
{
    int i = 0;
    while (i < len)
    {
        if (i > 0)
            write(1, " ", 1);
        char buf[12];
        int n = subset[i], j = 11;
        buf[11] = '\0';
        int neg = 0;
        if (n == 0)
            buf[10] = '0';
        else
        {
            if (n < 0)
            {
                neg = 1;
                n = -n;
            }
            while (n > 0)
            {
                buf[--j] = (n % 10) + '0';
                n /= 10;
            }
            if (neg)
                buf[--j] = '-';
        }
        write(1, buf + j, 11 - j);
        i++;
    }
    write(1, "\n", 1);
}

void backtrack(int *set, int set_len, int *subset, int sub_len, int target, int idx, int sum)
{
    if (sum == target)
    {
        print_subset(subset, sub_len);
    }
    int i = idx;
    while (i < set_len)
    {
        subset[sub_len] = set[i];
        backtrack(set, set_len, subset, sub_len + 1, target, i + 1, sum + set[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return 1;
    int target = ft_atoi(argv[1]);
    int set_len = argc - 2;
    int *set = (int *)malloc(sizeof(int) * set_len);
    int *subset = (int *)malloc(sizeof(int) * set_len);
    if (!set || !subset)
        return 1;
    int i = 0;
    while (i < set_len)
    {
        set[i] = ft_atoi(argv[i + 2]);
        i++;
    }
    backtrack(set, set_len, subset, 0, target, 0, 0);
    free(set);
    free(subset);
    return 0;
}
