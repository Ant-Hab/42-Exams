#include <unistd.h>

int ft_isspace(char c)
{
    return (c <= 32);
}

void str_cap(char *s)
{
    int i = 0;
    while (s[i])
    {
         if (s[i] >= 'A' && s[i] <= 'Z')
             s[i] += 32;
         if ((s[i] >= 'a' && s[i] <= 'z') && ft_isspace(s[i - 1]))
             s[i] -= 32;
         write(1, &s[i++], 1);
    }
}

int	main(int ac, char **av)
{
	int	i = 1;

	if (ac > 1)
	{
		while (i < ac)
		{
			str_cap(av[i]);
			write(1, "\n", 1);
			i++;
		}
	}
	else
		write(1, "\n", 1);
	return (0);
}