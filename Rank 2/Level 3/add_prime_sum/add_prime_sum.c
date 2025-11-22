#include <unistd.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int	res = 0;

	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

void	ft_putnbr(int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	char c = n % 10 + '0';
	write(1, &c, 1);
}

int	is_prime(int n)
{
	int	i = 2;

	if (n < 2)
		return (0);
	while (i * i <= n)
	{
		if (n % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int	n;
	int	sum = 0;

	if (ac == 2)
	{
		n = ft_atoi(av[1]);
		while (n > 1)
		{
			if (is_prime(n))
				sum += n;
			n--;
		}
		ft_putnbr(sum);
		write(1, "\n", 1);
		return (0);
	}
	write(1, "0\n", 2);
	return (0);
}
