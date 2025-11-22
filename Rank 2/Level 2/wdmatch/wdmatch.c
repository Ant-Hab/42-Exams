#include <unistd.h>

int main(int ac, char **av)
{
    if (ac == 3)
    {
        const char *s1 = av[1];
        const char *s2 = av[2];
        int i = 0, j = 0;

        while (s1[i] && s2[j])
        {
            if (s1[i] == s2[j])
                i++;
            j++;
        }
        if (s1[i] == '\0')
            write(1, s1, i);
    }
    write(1, "\n", 1);
    return (0);
}
