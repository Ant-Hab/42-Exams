#include <unistd.h>

int ft_atoi(char *str)
{
    int res = 0;
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + (*str - '0');
        str++;
    }
    return res;
}
void ft_putnbr(int n)
{
    if (n >= 10)
        ft_putnbr(n / 10);
    char c = n % 10 + '0';
    write(1, &c, 1);
}

void ft_putstr(char *s)
{
    while (*s)
        write(1, s++, 1);
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        write(1, "\n", 1);
        return (0);
    }
	
    int i = 1, 
	n = ft_atoi(av[1]);
    while (i < 10)
    {
        ft_putnbr(i);
        ft_putstr(" x ");
        ft_putnbr(n);
        ft_putstr(" = ");
        ft_putnbr(i * n);
        write(1, "\n", 1);
        i++;
    }
}