// #define _GNU_SOURCE

// #include <unistd.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>

// #ifndef BUFFER_SIZE 
// #define BUFFER_SIZE 42
// #endif

// void print_stars(int flen)
// {
// 	while(flen > 0)
// 	{
// 		write(1, "*", 1);
// 		flen--;
// 	}
// }

// int process_input(char *filter)
// {
// 	int bytes_read = 0;
// 	int total_size = 0;
// 	char *input = NULL;
// 	char *temp;
// 	char buf[BUFFER_SIZE + 2];
// 	while((bytes_read = read(0, buf, BUFFER_SIZE + 2)) > 0)
// 	{
// 		temp = realloc(input, bytes_read + total_size + 2);
// 		if(!temp)
// 		{
// 			perror("allocation failed");
// 			free(input);
// 			return(1);
// 		}
// 		memmove(temp + total_size, buf, bytes_read);
// 		total_size += bytes_read;
// 		input = temp;
// 	}
	
// 	char *match;
// 	char *current = input;
// 	int flen = strlen(filter);

// 	while(*current)
// 	{
// 		match = memmem(current, strlen(current), filter, flen);
// 		if(match == current)
// 		{
// 			print_stars(flen);
// 			current += flen;
// 		}
// 		else
// 		{
// 			write(1, current, 1);
// 			current++;
// 		}
// 	}
// 	return(0);
// }

// int main(int argc, char **argv)
// {
// 	if(argc != 2 || !argv[1][0])
// 		return(1);
// 	else
// 		process_input(argv[1]);
// }

#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac != 2 || !av[1][0])
        return 1;
    char *s = NULL, buf[128];
    int len = 0, r;
    while ((r = read(0, buf, 128)) > 0)
    {
        s = realloc(s, len + r);
        if (!s)
            return 1;
        memmove(s + len, buf, r);
        len += r;
    }
    int fl = strlen(av[1]);
    for (int i = 0; i < len;)
    {
        if (memmem(s + i, len - i, av[1], fl) == s + i)
        {
            for (int j = 0; j < fl; j++)
                write(1, "*", 1);
            i += fl;
        }
        else
            write(1, s + i++, 1);
    }
    free(s);
    return 0;
}