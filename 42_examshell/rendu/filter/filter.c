#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac != 2 || !av[1][0])
        return 1;
    char *s = NULL, buf[128];
    int len = 0, r;
    while ((r = read(0, buf, 128)) > 0)
    {
        s = realloc(s, len + r);
        if (!s)
            return 1;
        memmove(s + len, buf, r);
        len += r;
    }
    int fl = strlen(av[1]);
    for (int i = 0; i < len;)
    {
        if (memmem(s + i, len - i, av[1], fl) == s + i)
        {
            for (int j = 0; j < fl; j++)
                write(1, "*", 1);
            i += fl;
        }
        else
            write(1, s + i++, 1);
    }
    free(s);
    return 0;
}
