#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac >= 2)
	{
		int	i;
		int	j;

		i = 0;
		while (av[1][i] && (av[1][i] == ' ' || av[1][i] == '\t'))
			i++;
		j = i;
		while (av[1][i] && av[1][i] != ' ' && av[1][i] != '\t')
			i++;
		while (av[1][i] && (av[1][i] == ' ' || av[1][i] == '\t'))
			i++;
		while (av[1][i])
		{
			while ((av[1][i] && (av[1][i] != ' ' && av[1][i] != '\t')) &&
				(av[1][i - 1] == ' ' || av[1][i - 1] == '\t'))
			{
				while (av[1][i] && (av[1][i] != ' ' && av[1][i] != '\t'))
				{
					write(1, &av[1][i], 1);
					i++;
				}
				write(1, " ", 1);
				i++;
			}
			while (av[1][i] && av[1][i] != ' ' && av[1][i] != '\t')
				i++;
			while (av[1][i] && (av[1][i] == ' ' || av[1][i] == '\t'))
				i++;
		}
		while (av[1][j] && (av[1][j] != ' ' && av[1][j] != '\t'))
		{
			write(1, &av[1][j], 1);
			j++;
		}
	}
	write(1, "\n", 1);
	return (0);
}