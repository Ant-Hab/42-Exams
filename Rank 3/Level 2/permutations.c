#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

void ft_swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

char *ft_strdup(char *s)
{
    int len = ft_strlen(s);
    char *dup = (char *)malloc(len + 1);
    int i = 0;
    if (!dup)
        return NULL;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

void sort_string(char *s)
{
    int i = 0;
    int j;
    int len = ft_strlen(s);
    while (i < len - 1)
    {
        j = i + 1;
        while (j < len)
        {
            if (s[i] > s[j])
                ft_swap(&s[i], &s[j]);
            j++;
        }
        i++;
    }
}

void permute(char *s, int l, int r)
{
    int i;
    if (l == r)
    {
        write(1, s, r + 1);
        write(1, "\n", 1);
        return;
    }
    i = l;
    while (i <= r)
    {
        ft_swap(&s[l], &s[i]);
        permute(s, l + 1, r);
        ft_swap(&s[l], &s[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    char *s = ft_strdup(argv[1]);
    if (!s)
        return 1;
    sort_string(s);
    permute(s, 0, ft_strlen(s) - 1);
    free(s);
    return 0;
}
