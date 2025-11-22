#include "unistd.h"

int	main(int ac, char **av)
{
	int i;
	int j;
	int word;

	i = 0;
	j = 0;
	word = 0;
	if (ac == 2)
	{
		while (av[1][i])
			i++;
		i--;
		while (i >= 0)
		{
			while (i >= 0 && (av[1][i] == ' ' || av[1][i] == '\t'))
				i--;
			j = i;
			while (j >= 0 && av[1][j] != ' ' && av[1][j] != '\t')
				j--;
			if (word)
				write(1, " ", 1);
			write(1, &av[1][j + 1], i - j);
			word = 1;
			i = j;
		}
	}
	write(1, "\n", 1);
	return (0);
}