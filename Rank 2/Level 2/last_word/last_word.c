#include <unistd.h>

int main(int ac, char **a)
{
	if (ac == 2)
	{
		int i = 0;
		int j = 0;

		while (a[1][i])
			i++;
		i--;
		while (i >= 0 && (a[1][i] == ' ' || (a[1][i] >= 9 && a[1][i] <= 13)))
			i--;
		j = i;
		while (i >= 0 && a[1][i] > 32)
			i--;
		i++;
		while (i <= j)
			write(1, &a[1][i++], 1);
	}
	write(1, "\n", 1);
}
