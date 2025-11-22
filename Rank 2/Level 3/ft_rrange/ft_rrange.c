#include <stdlib.h>

int *ft_rrange(int start, int end)
{
    int i = 0;
    int len;
    
    if (end > start)
        len = end - start + 1;
    else
        len = start - end + 1;
    
    int *range = malloc(sizeof(int) * len);
    if (!range)
        return (NULL);
    
    while (i < len)
    {
        if (end < start)
            range[i] = end + i;
        else
            range[i] = end - i;
        i++;
    }
    return (range);
}