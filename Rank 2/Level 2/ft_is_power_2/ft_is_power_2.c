int	    is_power_of_2(unsigned int n)
{
	int i = 1;

	while (i <= n)
	{
		if (i == n)
			return  (1); 
		i = i * 2;
	}
	return (0);
}

// int	is_power_of_2(unsigned int n)
// {
// 	if (n == 0)
// 		return (0);
// 	return ((n & (n - 1)) == 0);
// }


// #include <stdio.h>
// int main()
// {
// 	printf("%d", is_power_of_2(16));
// }