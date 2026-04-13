#include <stdio.h>
#include <stdlib.h>

char *s;

int expr();

void error()
{
	if (!*s || *s == '\n')
		printf("Unexpected end of input\n");
	else
		printf("Unexpected token '%c'\n", *s);
	exit(1);
}

int factor()
{
	if (*s == '(')
	{
		s++;
		int res = expr();
		if (*s != ')')
			error();
		s++;
		return (res);
	}
	if (*s >= '0' && *s <= '9')
	{
		int res = *s - '0';
		s++;
		return (res);
	}
	error();
	return (0);
}

int term()
{
	int res = factor();
	while (*s == '*')
	{
		s++;
		res *= factor();
	}
	return (res);
}

int expr()
{
	int res = term();
	while (*s == '+')
	{
		s++;
		res += term();
	}
	return (res);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		s = av[1];
		if (!*s)
			return (0);
		int res = expr();
		if (*s && *s != '\n')
			error();
		printf("%d\n", res);
	}
	return (0);
}
