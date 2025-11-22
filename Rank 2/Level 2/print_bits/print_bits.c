#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int		i = 8;
	char	res = 0;

	while (i--)
	{
		res = ((octet >> i) & 1) + '0';
		write(1, &res, 1);
	}
}
